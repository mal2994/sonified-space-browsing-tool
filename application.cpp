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

int Application::find_index(int id, int num, Touch touches[])
{
   int i;

   for (i = 0; i < num; i++) {
      if (touches[i].id == id) {
         return i;
      }
   }

   return -1;
}

int Application::id_gesture(){
	//touches[i].
}

int Application::touch_main()
{
//   while (!application.quit) {
		if(accept_more_touches){
      if (!background && al_is_event_queue_empty(queue)) {
         al_clear_to_color(al_map_rgb(255, 255, 255));
         draw_touches(num_touches, touches);
         al_flip_display();
      }
      al_wait_for_event(queue, &event);
      switch (event.type) {
         case ALLEGRO_EVENT_DISPLAY_CLOSE:
            quit = true;	
            break;
         case ALLEGRO_EVENT_TOUCH_BEGIN: {
            int i = num_touches;
            if (num_touches < MAX_TOUCHES) {
               touches[i].id = event.touch.id;
               touches[i].x = event.touch.x;
               touches[i].y = event.touch.y;
               num_touches++;
            }
            break;
         }
         case ALLEGRO_EVENT_TOUCH_END: {
            int i = find_index(event.touch.id, num_touches, touches);
            if (i >= 0 && i < num_touches) {
               touches[i] = touches[num_touches - 1];
               num_touches--;
					accept_more_touches = false;
            }
			quit = true;
            break;
         }
         case ALLEGRO_EVENT_TOUCH_MOVE: {
            int i = find_index(event.touch.id, num_touches, touches);
            if (i >= 0) {
               touches[i].x = event.touch.x;
               touches[i].y = event.touch.y;

            }
            break;
         }
			//timer event rrm
			if(event.type == ALLEGRO_EVENT_TIMER) {
				cout << "measure: " << measureNumber++ << "\n";
			}
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
   }
	
		for(int i = 0;i<=num_touches-1;i++)
		{
			printf("id = %d, x = %d, y = %d \n",touches[i].id,touches[i].x,touches[i].y);
		}

   return 0;
}

//APPLICATION
Application::Application()
{
    display = NULL;
    timer = NULL;
    event_queue = NULL;
	 
	 num_touches = 0;
	 quit = false;
	 background = false;
	 Touch touches[MAX_TOUCHES];//
	 accept_more_touches = true;
	 measureNumber = 0;
}

Application::~Application()
{
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
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
	//make window for touch screen 
	display = al_create_display(800, 600);
	if (!display) {
		return -1;
	}
	//initialize allegro primitives
	al_init_primitives_addon();
   if (!al_install_touch_input()) {
//      abort_example("Could not init touch input.\n");
   }
	//create animation timer
	timer = al_create_timer(1.0 / FPS); 
   if (!timer)
   {
      al_destroy_timer(timer);
      al_destroy_display(display);
      return -1;
   }
	//create metronome 
	// ...to be written...seconds per frame, seconds per beat
	
	//in the queue go the signals from the different threads, touch input, display window, timer 
	//use multiple event queues to prevent having to poll the queue 
	queue = al_create_event_queue();
	if (!queue)
   {
      al_destroy_event_queue(queue);
      al_destroy_timer(timer);
      al_destroy_display(display);
      return -1;
    }
	al_register_event_source(queue, al_get_touch_input_event_source());
   al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_timer_event_source(timer));
	///al_register_event_source(queue, al_get_keyboard_event_source());
	
	
	
   return 0;
}

/*int Application::createWindow(float FPS, int width, int height)
{
	display = al_create_display(width, height);
    if (!display)
    {
        al_destroy_display(display);
        return -1;
    }

    timer = al_create_timer(1.0 / FPS);
    if (!timer)
    {
        al_destroy_timer(timer);
        al_destroy_display(display);
        return -1;
    }
	
    event_queue = al_create_event_queue();
    if (!event_queue)
    {
        al_destroy_event_queue(event_queue);
        al_destroy_timer(timer);
        al_destroy_display(display);
        return -1;
    }

    ///al_install_keyboard();
    ///al_init_image_addon();

    //al_register_event_source(event_queue, al_get_display_event_source(display));
    //al_register_event_source(event_queue, al_get_timer_event_source(timer));
    ///al_register_event_source(event_queue, al_get_keyboard_event_source());
	 return 0;
}*/

void Application::appLoop(void)
{
	//create user
	//User User1;
	cout << "User Created." << "\n";
	cout << "coords: " << User1.getTrueX() << ", " << User1.getTrueY() << "\n";

	//create rabbits
	//Rabbit AllRabbits[TOTALRABBITS];

	// user teleport
	User1.teleport(5,10);
	/*User1.setTrueX(5);
	User1.setTrueY(10);
	cout << "User teleported." << "\n";
	cout << "coords: " << User1.getTrueX() << ", " << User1.getTrueY() << "\n";*/

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
	while(1)
	{
		touch_main();
	}
	//return 0;
}