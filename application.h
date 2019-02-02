#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <allegro5/allegro.h>


#include "rabbit.h"
#include "user.h"
///#include "touch.h" for compilethis.sh and removed touch.h from gcc


using namespace std;
//not good that this is all global lol 
#define MAX_TOUCHES 7

/*ALLEGRO_DISPLAY *display;
ALLEGRO_TIMER *timer;
ALLEGRO_EVENT_QUEUE *event_queue;
ALLEGRO_EVENT_QUEUE *queue;
ALLEGRO_EVENT event;

 
int num_touches;
bool background; 
bool quit;*/

typedef struct TOUCH TOUCH;
struct TOUCH {
//class TOUCH {
public:
   int id;
   int x;
   int y;
};
static void draw_touches(int num, TOUCH touches[]);
static int find_index(int id, int num, TOUCH touches[]);
int touch_main();

//TOUCH touches[MAX_TOUCHES];

class Application
{
public:
   Application();
   ~Application();

	TOUCH touches[MAX_TOUCHES];
   Rabbit AllRabbits[TOTALRABBITS];
	User User1;
	
	// maybe not public lol
	ALLEGRO_DISPLAY *display;
   ALLEGRO_TIMER *timer;
   ALLEGRO_EVENT_QUEUE *event_queue;
	ALLEGRO_EVENT_QUEUE *queue;
	ALLEGRO_EVENT event;
	
	///Keyboard keyboard;
	 
	int num_touches;
   bool background; 
	bool quit; //end comment
	
   int init();
   int createWindow(float FPS, int w, int h);
   void appLoop();
	int touch_main();

private:



};

#endif