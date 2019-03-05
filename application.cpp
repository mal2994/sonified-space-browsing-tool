#include <iostream>
#include <cstdlib>
#include <cmath>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "rabbit.h"
#include "user.h"
//#include "touch.h"
#include "application.h"
//#include "ssbtsound.h" //redefinition
#include <csound/csound.h>
#include <thread>
#include <signal.h>		// for sigaction
#include <unistd.h>		// for sigaction

using namespace std;

void createAndCompile(float);
void startAndPerform(void);
void my_handler(int);
void messAround(void);

CSOUND *csound;
thread t1;
thread t2;
bool cswaitstate = false;

void Application::draw_touches(int num, Touch touches[])
{
   int i;

   for (i = 0; i < num; i++) {
      int x = touches[i].x;
      int y = touches[i].y;
      al_draw_circle(x, y, 50, al_map_rgb(255, 0, 0), 4);
   }
}

int Application::which_finger(int id, int num, Touch touches[])
{
   int i;

   for (i = 0; i < num; i++) {
      if (touches[i].id == id) {
         return i;
      }
   }

   return -1;
}

gesture_t Application::id_gesture(){
	int radius1 = -1, radius2 = -1;
	bool no_center = true;
	float angle1 = 0, angle2 = 0;
	
	//if one finger (0based-numbering), its a tap.
	if(num_touches == 0)
		return TAP_GESTURE;
	
	//if two fingers...invalid for now. this would be pinch or pull.
	if(num_touches == 1)
		return INVALID_GESTURE;
	
	//if three fingers it is either a disc or wedge 
	if(num_touches == 2) {
		for(int i=0;i<3;i++)	{ //check all fingers
		
			//if one finger is at the center of the screen, it can be a valid disc or wedge
			//						 400						  400							  200 						200
			if((fingers[i].x < 500 && fingers[i].x > 300) && (fingers[i].y < 300 && fingers[i].y > 100)){
				no_center = false;
				cout << "you have at least one finger on the center of the screen \n";
				
				//get radii with absolute value of distance formula
				radius1 = abs(sqrt(pow(fingers[i].x - fingers[i+1%3].x, 2) + pow(fingers[i].y - fingers[i+1%3].y, 2))); //this is an integer, not a double. we are rounding.
				radius2 = abs(sqrt(pow(fingers[i].x - fingers[i+2%3].x, 2) + pow(fingers[i].y - fingers[1+2%3].y, 2))); //this is an integer, not a double. we are rounding.
				
				//get angles with some trig unit circle type stuff, also convert from radians to degress.
				angle1 = acos((fingers[i+1%3].x-400)/(sqrt(pow(fingers[i+1%3].x-400, 2) + pow(fingers[i+1%3].y-200, 2))))*(180.0/3.141592653589793238463);
				angle2 = acos((fingers[i+2%3].x-400)/(sqrt(pow(fingers[i+2%3].x-400, 2) + pow(fingers[i+2%3].y-200, 2))))*(180.0/3.141592653589793238463);

				//acos returns 0-180 for an entire circle. use reflection and offset to get us the 180-360 range in quadrants III and IV
				if(fingers[i+1%3].y < 200) angle1 = (angle1*-1)+360;
				if(fingers[i+2%3].y < 200) angle2 = (angle2*-1)+360;
			}
		}
		//we have looked through all of the fingers and found none of them were at the center:
		if(no_center){
			cout << "you have no fingers at the center of the screen.\n";
			return INVALID_GESTURE;
		}else{	//one of the fingers was at the center 
			//determine if disc or wedge
			if(abs(angle1-angle2)<40)
				return DISC_GESTURE;
			if(abs(angle1-angle2)>10 && abs(radius1-radius2)<100) //angles in degrees, radii in pixels
				return WEDGE_GESTURE;
		}
	}
	return INVALID_GESTURE;
}

int Application::touch_main()
{
	/*ssbtsound.*///createAndCompile(22.5); 
   while (!quit){ 
		// only draw when all other events are complete
		if (!background && al_is_event_queue_empty(queue)) { 	  // background is true when android/ios user switches apps.
			al_clear_to_color(al_map_rgb(255, 255, 255));
			draw_touches(num_touches, touches);
			al_flip_display();
		}
		
		//sit here until an event of any kind comes in 
		al_wait_for_event(queue, &event);
		
		//handle the events 
		switch (event.type) {
			
			//touch events
			if(accept_more_touches){ 										// slow down the input rate..only touch events in this if 
				case ALLEGRO_EVENT_TOUCH_BEGIN: { 						// modify to do motion gestures todo
					int i = num_touches;
					if (num_touches < MAX_TOUCHES) {						// num_touches can go up to 7 because of the touch screen spec
						touches[i].id = event.touch.id;					// these three lines log touches chronologically
						touches[i].x = event.touch.x;
						touches[i].y = event.touch.y;
						fingers[event.touch.id].x = event.touch.x;	// these two lines log touches by finger 
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
						//createAndCompile(22.5);
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
			}	
			//timer events 
			case ALLEGRO_EVENT_TIMER: {				
				//poll for which timer it is...todo
				//cout << "seconds timer \n";
				if (event.timer.source == metronome)
				{
					cout << "measure: " << measureNumber++ << "\n";
																								//if(accept_more_touches == false){ //this means they put in a touch and we need to recompile the csound 
					if(measureNumber>1 && cswaitstate==false){
						cswaitstate = true;
						cout << "start and perform!\n";
						thread t1(startAndPerform);
						//thread t2(messAround);
						t1.join();
					}
					
																								//}
					accept_more_touches = true;
					gesture_processed = false;
				}
			}
			
			//display events
			case ALLEGRO_EVENT_DISPLAY_CLOSE: // this event triggers OVER AND OVER AND OVER! idk what the problem is!
				if(measureNumber > 2){			 // tried to fix it with a timer. NOPE.
				//	quit = true; //why does this not work!
				//	cout << "you decided to quit  \n"; 
				}
				break;
			case ALLEGRO_EVENT_DISPLAY_HALT_DRAWING:
				background = true;
				al_acknowledge_drawing_halt(event.display.source);
				break;
			case ALLEGRO_EVENT_DISPLAY_RESUME_DRAWING:
				background = false;
				al_acknowledge_drawing_resume(event.display.source);
				break;
			case ALLEGRO_EVENT_DISPLAY_RESIZE:
				al_acknowledge_resize(event.display.source);
				break;
			
		}
		
		//when they lift up their fingers, that's the gesture we're locking in and we're not accepting more touches for a period of time 
		if(!accept_more_touches && !gesture_processed){
			currentGesture = id_gesture();
			switch(currentGesture)
			{
				case TAP_GESTURE:
					cout << "tap.\n";
					//printf("id = %d, x = %d, y = %d \n",touches[0].id,touches[0].x,touches[0].y);
					User1.teleport(touches[0].x,touches[0].y);
					gesture_processed = true;
					break;
				case DISC_GESTURE:
					cout << "disc\n";
					gesture_processed = true;
					break;
				case WEDGE_GESTURE:
					cout << "wedge\n";
					gesture_processed = true;
					break;
				case INVALID_GESTURE:
					cout << "invalid\n";
					gesture_processed = true;
					break;
				
			}
			
		/*for(int i = 0;i<3;i++)//num_touches;i++)
		{
			printf("[postmain][touches]id = %d, x = %d, y = %d \n",touches[i].id,touches[i].x,touches[i].y);
			printf("[postmain][fingers]id = %d, x = %d, y = %d \n",fingers[i].id,fingers[i].x,fingers[i].y);
		}*/
			
			
		}
	} //end while 
   return 0;
}

//APPLICATION
Application::Application()
{
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
}

Application::~Application()
{
   al_destroy_event_queue(queue);
   al_destroy_timer(timer);
	al_destroy_timer(metronome);
   al_destroy_display(display);
}

int Application::init()
{
	//initialize allegro
   if (!al_init())
   {
      return -1;
   }
	//install touch input
	if (!al_install_touch_input()) {
		return -1;
	}
	//make window in OS
	display = al_create_display(800, 480);
	if (!display) {
		return -1;
	}
	///fullscreen
	al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);
   al_set_new_display_flags(ALLEGRO_FULLSCREEN);
	//initialize allegro primitives
	al_init_primitives_addon();
   if (!al_install_touch_input()) {
//      abort_example("Could not init touch input.\n");
   }
	//create seconds timer
	timer = al_create_timer(1.0 / FPS); 
   if (!timer)
   {
      al_destroy_timer(timer);
      al_destroy_display(display);
      return -1;
   }
	al_start_timer(timer);
	//create metronome 
	metronome = al_create_timer(BPM_TO_16BARS(BPM)); //param in seconds 
   if (!metronome)
   {
      al_destroy_timer(metronome);
      al_destroy_display(display);
      return -1;
   }
	al_start_timer(metronome);
	//in the queue go the signals from the different threads, touch input, display window, timer 
	//use a single event queue to prevent having to poll both the queue AND the event!
	queue = al_create_event_queue();
	if (!queue)
   {
      al_destroy_event_queue(queue);
      al_destroy_timer(timer);
		al_destroy_timer(metronome);
      al_destroy_display(display);
      return -1;
   }
	//associate the queue and the event sources
	al_register_event_source(queue, al_get_touch_input_event_source());
   al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_register_event_source(queue, al_get_timer_event_source(metronome));
	
   return 0;
}

void Application::appLoop(void)
{
	//create user
	//User User1;
	cout << "User Created." << "\n";
	cout << "coords: " << User1.getTrueX() << ", " << User1.getTrueY() << "\n";

	//create rabbits
	//Rabbit AllRabbits[TOTALRABBITS];

	// user teleport
	//User1.teleport(5,10);

	// new rabbits
	AllRabbits[0].setTrueX(5);
	AllRabbits[0].setTrueY(5);
	AllRabbits[0].calcDistanceToUser(User1.getTrueX(), User1.getTrueY());
	cout << "AllRabbits[0] Created." << "\n";
	cout << "coords: " << AllRabbits[0].getTrueX() << ", " << AllRabbits[0].getTrueY() << "\n";
	cout << "distance to user: " << AllRabbits[0].getDistanceToUser() << "\n";
	
	AllRabbits[1].setTrueX(100);
	AllRabbits[1].setTrueY(300);
	AllRabbits[1].calcDistanceToUser(User1.getTrueX(), User1.getTrueY());
	cout << "AllRabbits[0] Created." << "\n";
	cout << "coords: " << AllRabbits[1].getTrueX() << ", " << AllRabbits[1].getTrueY() << "\n";
	cout << "distance to user: " << AllRabbits[1].getDistanceToUser() << "\n";

	User1.activateInsideRabbits(AllRabbits);
	

	struct sigaction sigIntHandler;
	sigIntHandler.sa_handler = my_handler;
	sigemptyset(&sigIntHandler.sa_mask);
	sigIntHandler.sa_flags = 0;
	sigaction(SIGINT, &sigIntHandler, NULL);
	createAndCompile(22.5);
	//thread t1(startAndPerform);
	//thread t2(*this->touch_main); //are you getting "invalid use of non-static member function ‘int Application::touch_main()’ "
//	thread t1(startAndPerform);
	touch_main();
	
	//return 0;
}

Application& Application::getApplication()
{
	return *this;
}

void messAround()
{
	cout << "going to sleep\n";
	sleep(5);
	cout << "that was a good nap\n";
}

void startAndPerform()
{
	int result = 0;
	//while(1) createAndCompile(22.5); putting this in apploop initialize
	cout << "startAndPerform() csoundPerformKsmps\n";
	result = csoundStart(csound);
	result = 0;
	//while (result == 0)	result = csoundPerformKsmps(csound);
	while (1) {
		result = csoundPerformKsmps(csound);
		if (result != 0) {
		  break;
		}
	}
	cout << "startAndPerform() result != 0, join thread.\n";
	cswaitstate = false;
	//t1.join();	//dont do this...the thread will kill itself prematurely
}

void createAndCompile(float kazim) //now removing play code 7:49 3-2-19
{
// TODO: put this in a class
// BEGIN SSBTSOUND "CLASS"
//void createAndCompile(float);
//void startAndPerform(void);
char *csd_text1 =
"	<CsoundSynthesizer>\n"
"	<CsOptions>\n"
"	; combined gen01.csd and ../csound-vbaplsinit/test.csd \n"
"	; Select audio/midi flags here according to platform \n"
"	-odac     ;;;realtime audio out \n"
"	;-iadc    ;;;uncomment -iadc if realtime audio input is needed too \n"
"	; For Non-realtime ouput leave only the line below: \n"
"	; -o gen01.wav -W ;;; for file output any platform \n"
"	</CsOptions>\n"
"	<CsInstruments>\n"
"	sr = 44100 \n"
"	ksmps = 16\n"
"	nchnls = 8 \n"
"	0dbfs  = 1\n"
"	vbaplsinit 2, 8, 0, 72, 144, 216, 288, 0, 0, 0\n"
"	instr 1	;plays deferred and non-deferred sounds with loscil\n"
"	ifn = p4\n"
"	ibas = 1\n"
"	asig loscil 1, 1, ifn, ibas\n"
"	kazim=90\n"
"	a1,a2,a3,a4,a5,a6,a7,a8 vbap8  asig, kazim, 0, 1        ;change azimuth of soundsource\n"
"		  outo a1,a2,a3,a4,a5,a6,a7,a8\n"
"	endin\n"
"	instr 2\n"
"	ifn = p4\n"
"	ibas = 1\n"
"	asig loscil 1, 1, ifn, ibas\n"
"	kazim=180\n"
"	a1,a2,a3,a4,a5,a6,a7,a8 vbap8  asig, kazim, 0, 1        ;change azimuth of soundsource\n"
"		  outo a1,a2,a3,a4,a5,a6,a7,a8\n"
"	endin     \n"
"	instr 3\n"
"	ifn = p4\n"
"	ibas = 1\n"
"	asig loscil 1, 1, ifn, ibas\n"
"	kazim=270\n"
"	a1,a2,a3,a4,a5,a6,a7,a8 vbap8  asig, kazim, 0, 1        ;change azimuth of soundsource\n"
"		  outo a1,a2,a3,a4,a5,a6,a7,a8\n"
"	endin\n"
"	</CsInstruments>\n"
"	<CsScore>\n"
"	f 1 0 	0   1 \"drum_c_loop_32.wav\" 	0 0 0			;non-deferred sound\n"
"	f 2 0    0   1 \"mbass_c_loop.wav\"   0 0 0			;& deferred sounds in \n"
"	f 3 0    0   1 \"macc_c_loop.wav\" 	0 0 0			;different formats					\n"
"	i 1 0 32 1\n"
"	i 2 0 32 2	;non-deffered sound for instr. 2 ;im thinkin p4 selects sample \n"
"	i 3 0 32 3\n"
"	e\n"
"	</CsScore>\n"
"	</CsoundSynthesizer>";
char *csd_text2;
char *csd_textf = (char*)malloc(sizeof(char)*(2000));

//END SSBTSOUND "CLASS"
	int result;
	printf("createAndCompile entered: %f\n",kazim);
//	sprintf(csd_textf,"%s22%s",csd_text1,/*kazim,*/csd_text2);
	sprintf(csd_textf,"%s",csd_text1);
	csound = csoundCreate(0);
	printf("createAndCompile CSOUND CREATED\n");
	result = csoundCompileCsdText(csound,csd_textf);
	printf("createAndCompile CSOUND COMPILED\n");
//	result = csoundStart(csound); move to startAndPerform()
	/*while (1) {
		result = csoundPerformKsmps(csound);
		if (result != 0) {
			break;
		}
	}
	result = csoundCleanup(csound);
  	csoundReset(csound);*/
}
void my_handler(int s){
           printf("Caught signal %d\n",s);
           csoundDestroy(csound);
           t1.join();
           t2.join();
           exit(1); 
}

