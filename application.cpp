// some keywords to search for when making new patches: TODO, CHANGE, MOVED, or just /*
#include <iostream>
#include <cstdlib>
#include <cmath>        // for pow()
#include <allegro5/allegro_image.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "rabbit.h"
#include "user.h"
//#include "touch.h"     //redefinition
#include "application.h"
//#include "ssbtsound.h" //redefinition
#include <csound/csound.hpp>
#include <csound/csPerfThread.hpp>
#include <signal.h>		// for sigaction
#include <unistd.h>		// for sigaction
using namespace std;

/*void createAndCompile(void);
void endAndDestroyCsound(void);
void ctrlcHandler(int);
void messAround(void);
Csound* csound;
CsoundPerformanceThread* perfThread;
bool cswaitstate = false;
float r0distance = 0.0;
void ctrlcHandler(int);
void messAround(void); moved */

// APPLICATION CONSTRUCTOR
Application::Application(){
	display = NULL;
	timer = NULL;
	metronome = NULL;
	queue = NULL;
	num_touches = 0;
	quit = false;
	background = false;
	Touch touches[MAX_TOUCHES];
	accept_more_touches = true;
	gesture_processed = false;
	measureNumber = 0;
	currentGesture = INVALID_GESTURE; //have to initialize it to something or other
  //Ssbtsound ssbtsound;
  //struct sigaction sigIntHandler;
//  sigIntHandler.sa_handler = ctrlcHandler;//*this->ctrlcHandler(0);	//todo make this work 
  sigemptyset(&sigIntHandler.sa_mask);
  sigIntHandler.sa_flags = 0;
  sigaction(SIGINT, &sigIntHandler, NULL);

  if(initAllegro5()==-1){
    cout << "Fatal Error: Allegro 5 Could Not Be initialized. \n";
    exit(0);
  }
  initAllRabbits();
}
// APPLICATION DESTRUCTOR
Application::~Application(){
   al_destroy_event_queue(queue);
   al_destroy_timer(timer);
	 al_destroy_timer(metronome);
   al_destroy_display(display);
}

Application& Application::getApplication(){
	return *this;
}

int Application::initAllegro5(){
	//initialize allegro
   if (!al_init()){
     cout << "Could not create Allegro instance. \n";
     return -1;
   }
	/*//install touch input
	if (!al_install_touch_input()) {
		return -1;
	} CHANGE: looks like this was moved long ago...*/
	display = al_create_display(800, 480);                           // make window in OS
	if (!display) {
    cout << "Could not create display. \n";
		return -1;
	}
	al_get_display_mode(al_get_num_display_modes() - 1, &disp_data); // fullscreen
  al_set_new_display_flags(ALLEGRO_FULLSCREEN);                    // fullscreen
	al_init_primitives_addon();                                      // initialize allegro primitives
  if (!al_install_touch_input()) {                                 // install touch input
    cout << "Could not enable touch input. \n";
    al_destroy_display(display);
    return -1;
  }

	timer = al_create_timer(1.0 / FPS);                              // create seconds timer
  if (!timer){
    cout << "Could not create seconds timer. \n";
    al_destroy_timer(timer);
    al_destroy_display(display);
    return -1;
  }
	al_start_timer(timer);

  //create metronome
	metronome = al_create_timer(BPM_TO_16BARS(BPM));                 // create progression timer/metronome
  if (!metronome){
    cout << "Could not create metronome. \n";
    al_destroy_timer(metronome);
    al_destroy_display(display);
    return -1;
  }
	al_start_timer(metronome);                                       // ticks every 16 measures of 4 beats (aka a progression)

  // in the queue go the signals from the different threads, touch input, display window, timer
	// use a single event queue to prevent having to poll both the queue AND the event!
  queue = al_create_event_queue();
  if (!queue){
    cout << "Could not create event queue. \n";
    al_destroy_event_queue(queue);
    al_destroy_timer(timer);
    al_destroy_timer(metronome);
    al_destroy_display(display);
    return -1;
  }

  // associate the queue and the event sources
	al_register_event_source(queue, al_get_touch_input_event_source());
  al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_register_event_source(queue, al_get_timer_event_source(metronome));

  return 0;
}

void Application::draw_touches(int num, Touch touches[]){
   for (int i = 0; i < num; i++) {
      int x = touches[i].x;
      int y = touches[i].y;
      al_draw_circle(x, y, 50, al_map_rgb(255, 0, 0), 4);
   }
}

int Application::which_finger(int id, int num, Touch touches[]){
   for (int i = 0; i < num; i++) {
      if (touches[i].id == id) {
         return i;
      }
   }
   return -1;
}

gesture_t Application::id_gesture(){
	int radius1 = -1, radius2 = -1;
	float angle1 = 0, angle2 = 0;
  bool no_center = true;

	//if one finger (0based-numbering), its a tap.
	if(num_touches == 0) return TAP_GESTURE;

	//if two fingers...invalid for now. this would be pinch or pull.
	if(num_touches == 1) return INVALID_GESTURE;

	//if three fingers it is either a disc or wedge
	if(num_touches == 2) {
		for(int i = 0; i < 3; i++)	{ //check all fingers

			//if one finger is at the center of the screen (+/-100), it can be a valid disc or wedge
			if((fingers[i].x < CENTERX+100 && fingers[i].x > CENTERX-100) && (fingers[i].y < CENTERY+100 && fingers[i].y > CENTERY-100)){
				no_center = false;    // you have at least one finger on the center of the screen
				cout << "you have at least one finger on the center of the screen \n";

				//get radii with absolute value of distance formula
				radius1 = abs(sqrt(pow(fingers[i].x - fingers[i+1%3].x, 2) + pow(fingers[i].y - fingers[i+1%3].y, 2))); //this is an integer, not a double. we are rounding.
				radius2 = abs(sqrt(pow(fingers[i].x - fingers[i+2%3].x, 2) + pow(fingers[i].y - fingers[1+2%3].y, 2))); //this is an integer, not a double. we are rounding.

				//get angles with some trig unit circle type stuff, also convert from radians to degress.
				angle1 = acos((fingers[i+1%3].x-400)/(sqrt(pow(fingers[i+1%3].x-400, 2) + pow(fingers[i+1%3].y-200, 2))))*(180.0/PI);
				angle2 = acos((fingers[i+2%3].x-400)/(sqrt(pow(fingers[i+2%3].x-400, 2) + pow(fingers[i+2%3].y-200, 2))))*(180.0/PI);

				//acos returns 0-180 for an entire circle. use reflection and offset to get us the 180-360 range in quadrants III and IV
				if(fingers[i+1%3].y < 200) angle1 = (angle1*-1)+360;
				if(fingers[i+2%3].y < 200) angle2 = (angle2*-1)+360;
			}
		}
		// we have looked through all of the fingers and found none of them were at the center:
		if(no_center){
			cout << "you have no fingers at the center of the screen.\n";
			return INVALID_GESTURE;
		}else{	//one of the fingers was at the center
			//determine if disc or wedge
			if(abs(angle1-angle2)<40)  // will this pass unit tests?
				return DISC_GESTURE;
			if(abs(angle1-angle2)>10 && abs(radius1-radius2)<100) //angles in degrees, radii in pixels
				return WEDGE_GESTURE;
		}
	}
	return INVALID_GESTURE;
}

int Application::touch_main(){
  while (!quit){

		// only draw when all other events are complete
		if (!background && al_is_event_queue_empty(queue)) { 	  // background is true when android/ios user switches apps.
      al_clear_to_color(al_map_rgb(255, 255, 255));
      draw_touches(num_touches, touches);
      al_flip_display();
		}

		// sit here until an event of any kind comes in
		al_wait_for_event(queue, &event);

		// handle the events
		switch (event.type) {

			// TOUCH EVENTS // /* my bracket matching functionality in Atom is literally broken here. some cases are blue and others purple also. */
			if(accept_more_touches) {                        // if touch screen is not in blocked state
				case ALLEGRO_EVENT_TOUCH_BEGIN: {              // motion gestures TODO
					int i = num_touches;
					if (num_touches < MAX_TOUCHES) {             // num_touches can go up to 7 because of the touch screen spec
						touches[i].id = event.touch.id;            // these three lines log touches chronologically
						touches[i].x = event.touch.x;
						touches[i].y = event.touch.y;
						fingers[event.touch.id].x = event.touch.x; // these two lines log touches by finger
						fingers[event.touch.id].y = event.touch.y;
						num_touches++;
					}
					break;
				}
  			case ALLEGRO_EVENT_TOUCH_END: {
  				int i = which_finger(event.touch.id, num_touches, touches);
  				if (i >= 0 && i < num_touches) {
  					touches[i] = touches[num_touches - 1];
  					num_touches--;
  					accept_more_touches = false; // this is reset by a timer event later in this function
  					//createAndCompile(22.5);  /*new loudness/panning -- move the rabbits*/
  				}
  					break;
  			}
  			case ALLEGRO_EVENT_TOUCH_MOVE: {
  				int i = which_finger(event.touch.id, num_touches, touches);
  				if (i >= 0) {
  					touches[i].x = event.touch.x;
  					touches[i].y = event.touch.y;
  					fingers[event.touch.id].x = event.touch.x;
  					fingers[event.touch.id].y = event.touch.y;
  				}
  				break;
				}
			} // end touch events (if accept_more_touches)
			// TIMER EVENTS //
			case ALLEGRO_EVENT_TIMER: {
				if (event.timer.source == metronome){       // poll for which timer it is with if statements
					cout << "measure: " << measureNumber++ << "\n";
					if(/*measureNumber%6>4 &&*/ ssbtsound.getCsWaitState()==false){
						ssbtsound.setCsWaitState(true);
						cout << "start and perform -- put code to update csound here!\n"; /*new wavs*/
					}
					accept_more_touches = true;                // move touch screen from blocked to ready
					gesture_processed = false;                 // move touch screen from running to ready
				}
			} // end timer events

			// DISPLAY EVENTS //
			case ALLEGRO_EVENT_DISPLAY_CLOSE:{ // this event triggers OVER AND OVER AND OVER! idk what the problem is!
				if(measureNumber > 2){			 // tried to fix it with a timer. NOPE.
				//	quit = true; //why does this not work!
				//	cout << "you decided to quit  \n";
				}
				break;
			}
			case ALLEGRO_EVENT_DISPLAY_HALT_DRAWING:{
				background = true;
				al_acknowledge_drawing_halt(event.display.source);
				break;
			}
			case ALLEGRO_EVENT_DISPLAY_RESUME_DRAWING:{
				background = false;
				al_acknowledge_drawing_resume(event.display.source);
				break;
			}
			case ALLEGRO_EVENT_DISPLAY_RESIZE:{
				al_acknowledge_resize(event.display.source);
				break;
			}
		} //end checking all events (switch (event.type))

		// when they lift up their fingers, that's the gesture we're locking in and we're not accepting more touches for a period of time
		if(!accept_more_touches && !gesture_processed){                                     // touch screen is blocked, input processing is ready to be processed.
			currentGesture = id_gesture();
			switch(currentGesture){
				case TAP_GESTURE:{
					cout << "GESTURE = tap.\n";
					User1.teleport(ssbtsound, AllRabbits,touches[0].x,touches[0].y); /*then move this :)*/
/*					AllRabbits[0].calcDistanceToUser(User1.getTrueX(), User1.getTrueY());
					cout << AllRabbits[0].getDistanceToUser() << " : distance to user \n";
				  r0distance = AllRabbits[0].getDistanceComplement();
					cout << "r0distance = " << AllRabbits[0].getDistanceComplement() <<"\n";
					csound->SetChannel("r0distance", AllRabbits[0].getDistanceComplement());                                       // pass complement of distance as float to csound for amplitude adjustment
          AllRabbits[0].calcAngleToUser(User1.getTrueX(), User1.getTrueY());
          cout << "r0angle = " << AllRabbits[0].getAngleToUser() << "\n";
          csound->SetChannel("r0angle", AllRabbits[0].getAngleToUser());  moved to teleport */
          gesture_processed = true;                                                     // move touch screen from blocked state to ready state
					break;
				}
				case DISC_GESTURE:{
					cout << "GESTURE = disc.\n";
					gesture_processed = true;
					break;
				}
				case WEDGE_GESTURE:{
					cout << "GESTURE = wedge.\n";
					gesture_processed = true;
					break;
				}
				case INVALID_GESTURE:{
					cout << "GESTURE = invalid.\n";
					gesture_processed = true;
					break;
				}
			} // end switch currentGesture
		} //end if accept_more_touches and !gesture_processed
	} //end while !quit
   return 0;
}
void Application::printTouches(){ // for debugging
  for(int i = 0;i<3;i++)//num_touches;i++)
  {
    printf("[PrintTouches][touches]id = %d, x = %d, y = %d \n",touches[i].id,touches[i].x,touches[i].y);
    printf("[PrintTouches][fingers]id = %d, x = %d, y = %d \n",fingers[i].id,fingers[i].x,fingers[i].y);
  }
}

void Application::initAllRabbits(void){
	cout << "User coords: " << User1.getTrueX() << ", " << User1.getTrueY() << "\n";
	int rx[NUMRABBITS] = {5, 400, 795};		/* TODO these are bugs if NUMRABBITS > 3 */
	int ry[NUMRABBITS] = {5, 200, 395};

	for(int i = 0; i < NUMRABBITS; i++){
		// a=rabbit_id, b=is_fox, c=is_rabbit, x=truex, y=truey, userx, usery
		AllRabbits[i].initRabbit(i,false,true,rx[i],ry[i],User1.getTrueX(),User1.getTrueY());
	}

	// without a disc or wedge we are effectively activating them all
	User1.activateInsideRabbits(AllRabbits);

	//start the program


	//return 0;
}

void Application::messAround(){
	cout << "going to sleep\n";
	sleep(5);
	cout << "that was a good nap\n";
}

void Application::ctrlcHandler(int s){
	printf("Caught signal %d\n",s);
	//endAndDestroyCsound();   /* CHANGE: the destructor will take care of this now */
	exit(0);
}
