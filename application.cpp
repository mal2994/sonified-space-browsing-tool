#include <iostream>
#include <cstdlib>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "rabbit.h"
#include "user.h"
//#include "touch.h"
#include "application.h"

using namespace std;

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
	//touches[i].
	gesture_t x = TAP_GESTURE; // OK
	
	return x;
}

int Application::touch_main()
{
   while (!quit){ 
		// only draw when all other events are complete
		if (!background && al_is_event_queue_empty(queue)) { // background is true when android/ios user switches apps.
			al_clear_to_color(al_map_rgb(255, 255, 255));
			draw_touches(num_touches, touches);
			al_flip_display();
		}
		
		//sit here until an event of any kind comes in 
		al_wait_for_event(queue, &event);
		
		//handle the events 
		switch (event.type) {
			
			//touch events
			if(accept_more_touches){ //slow down the input rate..only touch events in this if 
				case ALLEGRO_EVENT_TOUCH_BEGIN: {
					int i = num_touches;
					//dont store more touches than you can have:
					if (num_touches < MAX_TOUCHES) {
						touches[i].id = event.touch.id;
						touches[i].x = event.touch.x;
						touches[i].y = event.touch.y;
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
					}
					break;
				}
				case ALLEGRO_EVENT_TOUCH_MOVE: {
					int i = which_finger(event.touch.id, num_touches, touches);
					if (i >= 0) {
						touches[i].x = event.touch.x;
						touches[i].y = event.touch.y;
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
					accept_more_touches = true;
					gesture_processed = false;
				}
			}
			
			//display events
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				///quit = true; why does this not work!	
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
	
		/* print all touches:
		for(int i = 0;i<=num_touches-1;i++)
		{
			printf("id = %d, x = %d, y = %d \n",touches[i].id,touches[i].x,touches[i].y);
		}*/
		
		//when they lift up their fingers, that's the gesture we're locking in and we're not accepting more touches for a period of time 
		if(!accept_more_touches && !gesture_processed){
			currentGesture = id_gesture();
			switch(currentGesture)
			{
				case TAP_GESTURE:
					cout << "tap.\n";
					printf("id = %d, x = %d, y = %d \n",touches[0].id,touches[0].x,touches[0].y);
					User1.teleport(touches[0].x,touches[0].y);
					gesture_processed = true;
					break;
				/*case DISC_GESTURE:
				case WEDGE_GESTURE:
				case INVALID_GESTURE: */
			}
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

	// new rabbit
	AllRabbits[0].setTrueX(5);
	AllRabbits[0].setTrueY(5);
	AllRabbits[0].calcDistanceToUser(User1.getTrueX(), User1.getTrueY());
	cout << "AllRabbits[0] Created." << "\n";
	cout << "coords: " << AllRabbits[0].getTrueX() << ", " << AllRabbits[0].getTrueY() << "\n";
	cout << "distance to user: " << AllRabbits[0].getDistanceToUser() << "\n";

	// create disc
	User1.getDisc1().activate(true);
	User1.getDisc1().setRadii(8,2);
	cout << "Disc created." << "\n";
	cout << "radius1: " << User1.getDisc1().getRadius1() << "\n";
	cout << "radius2: " << User1.getDisc1().getRadius2() << "\n";
	cout << "activated: " << User1.getDisc1().isActivated() << "\n";
	// activate (included in creating a disc)
	cout << "AllRabbits[0] activated? " << AllRabbits[0].isActivated() << "\n";
	User1.activateInsideRabbits(AllRabbits);
	cout << "AllRabbits[0] activated? " << AllRabbits[0].isActivated() << "\n";

	//wait for touch
	//while(1) loop forever within the function instead please.
	
		touch_main();
	
	//return 0;
}