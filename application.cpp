// some keywords to search for when making new patches: TODO, CHANGE, MOVED, or just
#include <iostream>
#include <cstdlib>
#include <cmath>        // for pow()
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include "rabbit.h"
#include "user.h"
//#include "touch.h"     //redefinition
#include "application.h"
#include "constants.h"
//#include "ssbtsound.h" //redefinition
#include <csound/csound.hpp>
#include <csound/csPerfThread.hpp>
#include <signal.h>		// for sigaction
#include <unistd.h>		// for sigaction
#include <thread>			// for threads
#include <time.h>
#include <fstream>		// for read from file
#include <sstream>		// for read from file
#include <string>		// for read from file
#include <vector>		// for read from file


using namespace std;

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
	gesture_identified = false;
	measureNumber = 0;
	currentGesture = NO_GESTURE;
	fox_voltage = 0;
	//mode_flags = {false, false, false, false, false, false, false, false};
  //Ssbtsound ssbtsound;
  //struct sigaction sigIntHandler;
//  sigIntHandler.sa_handler = ctrlcHandler;//*this->ctrlcHandler(0);	//todo make this work
  sigemptyset(&sigIntHandler.sa_mask);
  sigIntHandler.sa_flags = 0;
  sigaction(SIGINT, &sigIntHandler, NULL);
  found_fox = true;		// start program by reading from file
	draw_file_complete = false;
	draw_found = false;

}
// APPLICATION DESTRUCTOR
Application::~Application(){
   al_destroy_event_queue(queue);
   al_destroy_timer(timer);
	 al_destroy_timer(metronome);
   al_destroy_display(display);
	 gpiot.join();
}

Application& Application::getApplication(){
	return *this;
}

int Application::initAllegro5(){
	if (!al_init()){
	 cout << "Could not create Allegro instance. \n";
	 return -1;
	}

	// in the queue go the signals from the different threads, touch input, display window, timer
	// use a single event queue to prevent having to poll both the queue AND the event!
	queue = al_create_event_queue();
	if (!queue){
		cout << "Could not create event queue. \n";
		al_destroy_event_queue(queue);
//		al_destroy_timer(timer);
//		al_destroy_timer(metronome);
//		al_destroy_display(display);
		return -1;
	}

	if(mode_flags[TOUCH_FLAG]){
		al_init_font_addon();
		al_init_ttf_addon();
		al_init_primitives_addon();                           // primitivies are basic graphics
//		al_get_display_mode(al_get_num_display_modes() - 1, &disp_data); 		// fullscreen
//		al_set_new_display_flags(ALLEGRO_FULLSCREEN);                    		// fullscreen
		//display = al_create_display(disp_data.width, disp_data.height);                          // make window in OS
		display = al_create_display(SCREENW, SCREENH);                          // make window in OS
		if (!display){
			cout << "Could not create display. \n";
			return -1;
		}
		font = al_load_ttf_font("./AmaticSC-Regular.ttf", 64, 0);
		al_register_event_source(queue, al_get_display_event_source(display));	// associate display with event queue
		al_hide_mouse_cursor(display);																	 // hides cursor in the window
		if (!al_install_touch_input()){
		  cout << "Could not enable touch input. \n";
		  al_destroy_display(display);
		  return -1;
		}
		al_register_event_source(queue, al_get_touch_input_event_source());	// associate touch with event queue

	}else{
		// touch screen is off, use keyboard for user input
		/*if(!al_install_keyboard()) {
			cout <<"failed to initialize the keyboard!\n";
			return -1;
		}*/
		//al_register_event_source(queue, al_get_keyboard_event_source());
	}

	timer = al_create_timer(1.0 / FPS);										// how often data changed by sensors/file is sent to csound
  if (!timer){
    cout << "Could not create seconds timer. \n";
    al_destroy_timer(timer);														// its also in destructor..
    al_destroy_display(display);
    return -1;
  }

  //create metronome
	metronome = al_create_timer(BPM_TO_8BARS(BPM));				// how often data changed by user input is sent to csound
  if (!metronome){
    cout << "Could not create metronome. \n";
    al_destroy_timer(metronome);
    al_destroy_display(display);
    return -1;
  }
	ssbtsound.compileCsound(mode_flags);
	al_start_timer(metronome);                            // ticks every 8 measures of 4 beats (aka a progression)
	ssbtsound.startPerformanceThread();										// side by side to lock as tight as possible with metronome.
	al_start_timer(timer);
	//messAround();																				// todo does this fix a message pass before init bug? Dont Think It Does!
	User1.teleport(CENTERX,CENTERY); 											// this line just sets User1.truex and truey which are already set...
	initAllRabbits();
	calculateChannels();																	// calculate distances and angles
	ssbtsound.flipChannels(false);												// send the channels
																						// ^should be no issue with portability, as allegro 5 timer is mandatory

  // associate the queue and the event sources (no error checking and register them even if we dont have them? todo)
	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_register_event_source(queue, al_get_timer_event_source(metronome));


	// GPIO set up
//	pthread_create(&gpiot, NULL, *this->ssbtgpiot);// create thread for reading GPIO
	gpiot = this->makeThread();
  return 0;
}

thread Application::makeThread(){
	return thread([=]{ssbtgpiof();});
}

void Application::ssbtgpiof(){
/* GPIO_FLAG
	if(ssbtgpio.setUpPins() == 1){
		return;
	} */

		/* the gpio rabbit moving */ //mode_flags[GPIO_FLAG] etc..
//		AllRabbits[0].setTrueY(((float)(ssbtgpio.readChn(0) / 15)) * SCREENH);
//		AllRabbits[1].setTrueY(((float)(ssbtgpio.readChn(1) / 15)) * SCREENH);
//		AllRabbits[2].setTrueY(((float)(ssbtgpio.readChn(2) / 15)) * SCREENH);
//		AllRabbits[3].setTrueY(((float)(ssbtgpio.readChn(3) / 15)) * SCREENH);
//		fox_voltage = (((float)ssbtgpio.readChn(4) / 15) * SCREENH);

	return;
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

void Application::draw_gesture(){
	int radius1 = -1, radius2 = -1;						// all calculations are local to this function
	float angle1 = 0, angle2 = 0;
 	bool no_center = true;

 	// draw the center of the screen
 	al_draw_rectangle(CENTERX+CENTR_STY, CENTERY+CENTR_STY, CENTERX-CENTR_STY, CENTERY-CENTR_STY, al_map_rgb(64, 64, 64), 5);
	draw_touches(num_touches, touches);				// always draw fingers

	// draw file complete
	if(draw_file_complete){
		al_draw_text(font, al_map_rgb(0, 0, 0), 0, 0, 0, "YOU WIN!!!");
	}

	// if two fingers...invalid for now. this would be pinch or pull.
	//if(num_touches == 2) return;

	// if three fingers it is either a disc or wedge
	if(num_touches == 3) {
		for(int i = 0; i < 3; i++)	{ //check all fingers

			// if one finger is at the center of the screen (+/-100), it can be a valid disc or wedge
			if((fingers[i].x < CENTERX+100 && fingers[i].x > CENTERX-100) && (fingers[i].y < CENTERY+100 && fingers[i].y > CENTERY-100)){
				no_center = false;    // you have at least one finger on the center of the screen
//				cout << "you have at least one finger on the center of the screen \n";

				// get radii with absolute value of distance formula
				radius1 = abs(sqrt(pow(fingers[i].x - fingers[i+1%3].x, 2) + pow(fingers[i].y - fingers[i+1%3].y, 2))); //this is an integer, not a double. we are rounding.
				radius2 = abs(sqrt(pow(fingers[i].x - fingers[i+2%3].x, 2) + pow(fingers[i].y - fingers[1+2%3].y, 2))); //this is an integer, not a double. we are rounding.

				// get angles with some trig unit circle type stuff, also convert from radians to degress.
				angle1 = DEGTORAD(acos((fingers[i+1%3].x-CENTERX)/(sqrt(pow(fingers[i+1%3].x-CENTERX, 2) + pow(fingers[i+1%3].y-CENTERY, 2)))));
				angle2 = DEGTORAD(acos((fingers[i+2%3].x-CENTERX)/(sqrt(pow(fingers[i+2%3].x-CENTERX, 2) + pow(fingers[i+2%3].y-CENTERY, 2)))));

				// acos returns 0-180 for an entire circle. use reflection and offset to get us the 180-360 range in quadrants III and IV
				if(fingers[i+1%3].y < CENTERY) angle1 = (angle1*-1)+360;
				if(fingers[i+2%3].y < CENTERY) angle2 = (angle2*-1)+360;
			}
		}
		// we have looked through all of the fingers and found none of them were at the center:
		if(no_center){
//			cout << "you have no fingers at the center of the screen.\n";
				al_draw_circle(CENTERX, CENTERY, 100, al_map_rgb(255, 0, 0), 5);		//al_flip_display() will take care of these
				al_draw_circle(CENTERX, CENTERY, 200, al_map_rgb(255, 0, 0), 5);
			return;
		}else{	// one of the fingers was at the center
			if(abs(angle1-angle2)<GEST_ANGLE_STY && abs(radius1-radius2)>GEST_RADII_STY){
				al_draw_circle(CENTERX, CENTERY, radius1, al_map_rgb(255, 255, 0), 5);		//al_flip_display() will take care of these
				al_draw_circle(CENTERX, CENTERY, radius2, al_map_rgb(255, 255, 0), 5);
			}
			if(abs(angle1-angle2)>=GEST_ANGLE_STY && abs(radius1-radius2)<GEST_RADII_STY){
				//draw wedge
//				cout << "angle1 = " << angle1 << " angle2 = " << angle2 << "\n";
			}
		}
	}
	if(num_touches > 3) return; // too many touches
	return;
}

gesture_t Application::id_gesture(){
	int radius1 = -1, radius2 = -1;						// all calculations are local to this function
	float angle1 = 0, angle2 = 0;
 	bool no_center = true;

	// draw a tap.
	if(num_touches == 1) return TAP_GESTURE;

	// if two fingers...invalid for now. this would be pinch or pull.
	if(num_touches == 2) return INVALID_GESTURE;

	// if three fingers it is either a disc or wedge
	if(num_touches == 3) {
		for(int i = 0; i < 3; i++)	{ //check all fingers

			// if one finger is at the center of the screen (+/-100), it can be a valid disc or wedge
			if((fingers[i].x < CENTERX+CENTR_STY && fingers[i].x > CENTERX-CENTR_STY) && (fingers[i].y < CENTERY+CENTR_STY && fingers[i].y > CENTERY-CENTR_STY)){
				no_center = false;    // you have at least one finger on the center of the screen
//				cout << "you have at least one finger on the center of the screen \n";

				// get radii with absolute value of distance formula
				radius1 = abs(sqrt(pow(fingers[i].x - fingers[i+1%3].x, 2) + pow(fingers[i].y - fingers[i+1%3].y, 2))); //this is an integer, not a double. we are rounding.
				radius2 = abs(sqrt(pow(fingers[i].x - fingers[i+2%3].x, 2) + pow(fingers[i].y - fingers[1+2%3].y, 2))); //this is an integer, not a double. we are rounding.

				// get angles with some trig unit circle type stuff, also convert from radians to degress.
				angle1 = DEGTORAD(acos((fingers[i+1%3].x-CENTERX)/(sqrt(pow(fingers[i+1%3].x-CENTERX, 2) + pow(fingers[i+1%3].y-CENTERY, 2)))));
				angle2 = DEGTORAD(acos((fingers[i+2%3].x-CENTERX)/(sqrt(pow(fingers[i+2%3].x-CENTERX, 2) + pow(fingers[i+2%3].y-CENTERY, 2)))));

				// acos returns 0-180 for an entire circle. use reflection and offset to get us the 180-360 range in quadrants III and IV
				if(fingers[i+1%3].y < CENTERY) angle1 = (angle1*-1)+360;
				if(fingers[i+2%3].y < CENTERY) angle2 = (angle2*-1)+360;
			}
		}
		// we have looked through all of the fingers and found none of them were at the center:
		if(no_center){
//			cout << "you have no fingers at the center of the screen.\n";
			return INVALID_GESTURE;

		}else{	// one of the fingers was at the center
			if(abs(angle1-angle2)<GEST_ANGLE_STY && abs(radius1-radius2)>GEST_RADII_STY){
				User1.getDisc1().setRadii(radius1,radius2);
				return DISC_GESTURE;	// similar angles, dissimilar radii is disc
			}
			if(abs(angle1-angle2)>=GEST_ANGLE_STY && abs(radius1-radius2)<GEST_RADII_STY){
				User1.getWedge1().setAngles(angle1,angle2);
				return WEDGE_GESTURE;	// dissimilar angles, similar radii is wedge
			}
		}
	}
	if(num_touches > 3) return INVALID_GESTURE; // too many touches

	return NO_GESTURE;
}

int Application::touch_main(){
  while (!quit){

    if(mode_flags[TOUCH_FLAG]){ //if graphics/touch enabled.
		  // only draw when all other events are complete
			if (!background && al_is_event_queue_empty(queue)) { 	  // background is true when android/ios user switches apps.
						al_clear_to_color(al_map_rgb(255, 255, 255));
						if(draw_found) al_draw_circle(User1.getTrueX(), User1.getTrueY(), 50, al_map_rgb(0, 255, 0), 4); 	// draw user
						else al_draw_circle(User1.getTrueX(), User1.getTrueY(), 50, al_map_rgb(255, 0, 0), 4); 	// draw user
						draw_gesture();
						al_flip_display();
			}
		}

		// sit here until an event of any kind comes in
		al_wait_for_event(queue, &event);

		// handle the events
		switch (event.type) {

			// TOUCH EVENTS // /* my bracket matching functionality in Atom is literally broken here. some cases are blue and others purple also. */
			if(accept_more_touches) {                        // if touch screen is not in blocked state
				/*case ALLEGRO_EVENT_KEY_UP: {
					if (event.keyboard.keycode == ALLEGRO_KEY_UP) {
						//keyInCommand();
						accept_more_touches = false;
						gesture_identified = false;
					}
          break;
				} todo took keyboard out for testing.*/
		    if(mode_flags[TOUCH_FLAG]){ //if graphics/touch enabled.
				  case ALLEGRO_EVENT_TOUCH_BEGIN: {              // motion gestures TODO
					  int i = num_touches;
					  if (num_touches < MAX_TOUCHES) {
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
    				//int i = which_finger(event.touch.id, num_touches, touches);
    				//if (i >= 0 && i < num_touches) {
    				//	touches[i] = touches[num_touches - 1];
    				//	num_touches--;
    				accept_more_touches = false; 							// this is reset by a timer event later in this function
						gesture_identified = false;
						ssbtsound.csound->SetChannel("drumackamp",1.0);				// turn the drum acknowledge on

    				//}
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
			} //end touch enabled events
			// TIMER EVENTS //
			case ALLEGRO_EVENT_TIMER: {
				if (event.timer.source == metronome){       // poll for which timer it is with if statements
					if(!accept_more_touches && gesture_identified){
						switch(currentGesture){
							case TAP_GESTURE:{
//								cout << "GESTURE = tap.\n";
								User1.teleport(touches[0].x,touches[0].y);
								User1.getDisc1().activate(false);
								User1.getWedge1().activate(false);
								calculateChannels();
								calcFoxFound();
								if(found_fox){ // if user got the fox
									draw_found = true;
									for(int i=0; i<NUMRABBITS; i++){
										int result = 0;
										result = ssbtgpio.readFile();
										if(result == -1)	exit(0);
										else if(result == 0){}
										else if(result == 1) draw_file_complete = true;
										AllRabbits[i].setTrueX(((float)ssbtgpio.getPoint1()/15)*SCREENW);
										AllRabbits[i].setTrueY(((float)ssbtgpio.getPoint2()/15)*SCREENH);
										cout << "NEW POINTS rabbit 0 x = " << AllRabbits[0].getTrueX() << " y = " << AllRabbits[0].getTrueY() << "\n";
									}
								}else{
//									al_draw_circle(User1.getTrueX(), User1.getTrueY(), 50, al_map_rgb(0, 255, 255), 4); 	// draw user
										draw_found = false;
								}
								User1.activateInsideRabbits(AllRabbits);
								calculateChannels();
								break;
							}
							case DISC_GESTURE:{
//								cout << "GESTURE = disc.\n";
								User1.getDisc1().activate(true);
								User1.activateInsideRabbits(AllRabbits);
								calculateChannels();
								break;
							}
							case WEDGE_GESTURE:{
//								cout << "GESTURE = wedge.\n";
								// todo if no disc, can have no wedge. is that what we want to do?
								User1.getWedge1().activate(true);
								User1.activateInsideRabbits(AllRabbits);
								calculateChannels();
								break;
							}
							case INVALID_GESTURE:{
//								cout << "GESTURE = invalid.\n";
								User1.getDisc1().activate(false);
								User1.getWedge1().activate(false);
								calculateChannels();
								break;
							}
							case NO_GESTURE:{								// no gesture was made within a progression time frame
								break;
							}
						} //end switch currentGesture
						ssbtsound.flipChannels(true);
						accept_more_touches = true;
						gesture_identified = false;						// lock out id_gesture() to control flow
						currentGesture = NO_GESTURE;					// lock out switch currentGesture
						ssbtsound.setDrumAckAmp(0.0);					// turn off drum acknowledge
					//ssbtsound.setSwishAmp(0.0);//todo redundancy
						found_fox = false;
						num_touches = 0;								// an event will set this to 0, but we want to clear the display a little early.
					} //end if !accept_more_touches
				}else if(event.timer.source == timer){			// poll for which timer it is with if statements

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

		// when they lift up their fingers, that's the gesture we're locking in
		// and we're not accepting more touches until audio display flip
		if(!accept_more_touches && !gesture_identified){		// touch screen is blocked from taking more gestures &&
			currentGesture = id_gesture();
//			cout << "id_gesture = " << currentGesture << "\n";
			gesture_identified = true;						// lock us out from indentifying the same gesture many times

		} //end if accept_more_touches and !gesture_identified
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
	// place to put your first points read from file temporarily.
	int rx[NUMRABBITS] = {};
	int ry[NUMRABBITS] = {};

	// put the first points read from file in the temporary array
	for(int i=0; i<NUMRABBITS; i++){
		ssbtgpio.readFile();
		//AllRabbits[i].setTrueX((float)(ssbtgpio.getPoint1()/15)*SCREENW);
		//AllRabbits[i].setTrueY((float)(ssbtgpio.getPoint2()/15)*SCREENH);
		rx[i] = ((float)ssbtgpio.getPoint1()/15)*SCREENW;
		ry[i] = ((float)ssbtgpio.getPoint2()/15)*SCREENH;
	}

	// use the temporary array to instantiate rabbits
	for(int i = 0; i < NUMRABBITS; i++){
		// a=rabbit_id, b=is_fox, c=is_rabbit, x=truex, y=truey, userx, usery // put this here to help you write the next line
		AllRabbits[i].initRabbit(i,false,true,rx[i],ry[i],User1.getTrueX(),User1.getTrueY());
		cout << "NEW POINTS rabbit 0 x = " << AllRabbits[i].getTrueX() << " y = " << AllRabbits[i].getTrueY() << "\n";
	}
	User1.activateInsideRabbits(AllRabbits);		// without a disc or wedge we are effectively activating them all
}

void Application::messAround(){
	cout << "going to sleep\n";
	sleep(5);
	cout << "that was a good nap\n";
}

void Application::ctrlcHandler(int s){
	printf("Caught signal %d\n",s);
	exit(0);
}

void Application::calculateChannels(){
	// modify AllRabbits angles and distances
	for(int i = 0; i < NUMRABBITS; i++){
		AllRabbits[i].calcDistanceToUser(User1.getTrueX(), User1.getTrueY());    // sets distance and distance complement
		AllRabbits[i].calcAngleToUser(User1.getTrueX(), User1.getTrueY());
	}

	// mute all instruments so the instruments you want will become unmuted later
	for(int i = 0; i < NUMINSTR; i++){
		ssbtsound.setDistanceChn(i,0.0);
		ssbtsound.setAngleChn(i,0.0);
	}

	// send AllRabbits angles and distances to Csound
	for(int i = 0; i < NUMRABBITS; i++){
		if(AllRabbits[i].isActivated()){	// if Rabbit is activated, send its data to csound
			ssbtsound.setDistanceChn(AllRabbits[i].getRabbitId(),AllRabbits[i].getDistanceComplement());	// instrument swapping in parameter 1 of this line
			ssbtsound.setAngleChn(AllRabbits[i].getRabbitId(),AllRabbits[i].getAngleToUser());
		}else{	// if Rabbit is not activated, turn its volume off
			ssbtsound.setDistanceChn(AllRabbits[i].getRabbitId(),0.0);
		}
	}

	// calculate r2rdistances
	for(int i = 1; i < NUMRABBITS; i++){
		r2rdistances[i-1] = abs(sqrt(pow(AllRabbits[i].getTrueX() - AllRabbits[i-1].getTrueX(), 2) + pow(AllRabbits[i].getTrueY() - AllRabbits[i-1].getTrueY(), 2)));// this is an integer, not a double. we are rounding.
//		cout << "r2rdistances[i-1] = " << r2rdistances[i-1] << "\n";
	}

}

void Application::calcFoxFound(){
	// which rabbits are foxes?
/*	for(int i = 0; i < NUMRABBITS; i++){
		if(abs(AllRabbits[i].getTrueY() - fox_voltage) < FOX_STY){
			AllRabbits[i].setFox(true);
		}else{
			AllRabbits[i].setFox(false);				TODO fox_voltage NOT USED & ALWAYS TRUE thats why this is commented out
		}
	}*/

	// is user very close to a fox?
	ssbtsound.setSwishAmp(0.0);
	found_fox = false;
	for(int i = 0; i < NUMRABBITS; i++){
		//if(AllRabbits[i].isFox()){
			if (AllRabbits[i].getDistanceToUser() < SWISH_DIST){
				ssbtsound.setSwishAmp(1.0);
				rotateRabbits();		// change instruments
				found_fox = true;		// tell data acquisition thread to put new data in rabbits
				cout << "SWISH!\n";
			}
		//}
	}

	//return found_fox; could do that
}

void Application::rotateRabbits(){
  for(int i = 0; i < NUMRABBITS; i++){
    AllRabbits[i].setRabbitId((AllRabbits[i].getRabbitId()+1)%NUMINSTR);
		cout << "["<<i<<"]rabbitid = "<< AllRabbits[i].getRabbitId() << "\n";
  }
}

bool Application::convertArgv1(int num){
	int divisor = 10000000;							// 0x80
	unsigned char bitPos = 0x80;				// 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80
	unsigned char answer = 0x00;
	bool valid = true;
	for(int i = 7; i >= 0; i--){
		if (num/divisor == 1){
			mode_flags[i*-1+7] = true;			// use reflection & offset to make downcounter an upcounter i*-1+7
			answer += bitPos;
			num -= divisor;
		}else if (num/divisor != 0){
			valid = false;
			break;
		}
		bitPos /= 2;
		divisor /= 10;
	}
	return valid;
}

void Application::echoMode(){
	//cout << "SETTING OPTIONS... --------------------------------------------\n";
//	cout << "---------------------------------------------------------------\n";
	cout << "MODES SELECTED: ";
	if(mode_flags[R2R_FLAG] == true)cout << "Rabbit to rabbit enabled. User to rabbit disabled. ";
	if(mode_flags[STEREO_FLAG] == true)cout << "Stereo sound enabled. ";
	else if(mode_flags[SUR51_FLAG] == true)cout << "5.1 sound enabled. ";
	else if(mode_flags[SUR71_FLAG] == true)cout << "7.1 sound enabled. ";
	else{																																						// no sound setting selected
		 cout << "Stereo sound enabled. ";
		 mode_flags[STEREO_FLAG] = true;
	}
	if(mode_flags[TOUCH_FLAG] == true)cout << "Touch enabled. ";
	if(mode_flags[HRTF_FLAG] == true && mode_flags[STEREO_FLAG] == true)cout << "HRTF enabled ";
//	if(mode_flags[0] == true)cout << "FLAG 0 IS DUMMY.\n";
//	if(mode_flags[1] == true)cout << "FLAG 1 IS DUMMY.\n";
cout << "\n";
}

void Application::askMode(){
	char response = 'n';
	cout << "---------------------------------------------------------------\n";
	cout << "--------------------- I/O SETTINGS MENU -----------------------\n";
	cout << "------------------------------&--------------------------------\n";
	cout << "Correct usage: ./ssbt 11111111\n";
	cout << "STEREO SOUND? (y/n) ";
	cin >> response;
	if(response == 'y'){
		mode_flags[STEREO_FLAG] = true;												// 2.0 stereo mode
		cout << "HRTF? (recommended yes) (y/n) ";							// if stereo, hrtf available
		cin >> response;
		if(response == 'y'){
			mode_flags[HRTF_FLAG] = true;												// stereo hrtf mode
		}
	}else{																									// not stereo, 5.1 or 7.1?
		cout << "5.1 SOUND? (y/n) ";
		cin >> response;
		if(response == 'y'){
			mode_flags[SUR51_FLAG] = true;											// 5.1 surround mode
		}else{
			cout << "7.1 SOUND? (y/n) ";
			if(response == 'y') mode_flags[SUR71_FLAG] = true;	// 7.1 surround mode
			else mode_flags[STEREO_FLAG] = true;								// if not 5.1 or 7.1 make it 2.0 stereo no hrtf
		}
	}
	cout << "RABBIT TO RABBIT SOUND? (y/n) ";
	cin >> response;
	if(response == 'y') mode_flags[R2R_FLAG] = true;					// rabbit to rabbit enabled, user to rabbit disabled
	cout << "TOUCH SCREEN? (y/n) ";
	cin >> response;
	if (response == 'y'){
		mode_flags[TOUCH_FLAG] = true;												// touch enabled
	}
	cout << "---------------------------------------------------------------\n";
	cout << "------------------------- I/0 CONFIG --------------------------\n";
	cout << "------------------------------&--------------------------------\n";
	cout << "TIP: Use this command to start up in this mode:\n";
	cout << "./ssbt " << mode_flags[0] << mode_flags[1] << mode_flags[2] << mode_flags[3] << mode_flags[4] << mode_flags[5] << mode_flags[6] << mode_flags[7] << "\n";
}

void Application::modesDefault(void){
	mode_flags[R2R_FLAG] = false;
	mode_flags[STEREO_FLAG] = false;
	mode_flags[SUR51_FLAG] = true;
	mode_flags[SUR71_FLAG] = false;
	mode_flags[TOUCH_FLAG] = true;
	mode_flags[HRTF_FLAG] = false;
}

/*
gesture_t Application::keyInCommand(){
	char command[13];
	int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
	cout << "COMMAND: ";
	cin	<< command;
	if(command[0] == 't'){
		x1 = 100*command[1] + 10*command[2] + 1*command[3];
		y1 = 100*command[4] + 10*command[5] + 1*command[6];
	}//else if (command[0] == '
}*/
