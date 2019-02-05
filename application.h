#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <allegro5/allegro.h>
#include "rabbit.h"
#include "user.h"

using namespace std;

#define MAX_TOUCHES 	 7
#define FPS				30

/*typedef struct TOUCH TOUCH;
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
*/
//TOUCH touches[MAX_TOUCHES];

class Touch
{
	public:
		int id;
		int x;
		int y;
};

class Application
{
public:
   Application();
   ~Application();

	Touch touches[MAX_TOUCHES];
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
	bool quit;
	bool accept_more_touches;
	int measureNumber;
	
   int init();
   //int createWindow(float FPS, int w, int h);
   void appLoop();
	void timerLoop();
	int touch_main();
	
	void draw_touches(int num, Touch touches[]);
	int find_index(int id, int num, Touch touches[]);
	
	int id_gesture();

private:

};

#endif