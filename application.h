// some keywords to search for when making new patches: TODO, CHANGE, MOVED, or just /*
#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <signal.h>		// for sigaction
#include <unistd.h>		// for sigaction
#include <allegro5/allegro.h>
#include "rabbit.h"
#include "user.h"
#ifndef SSBTSOUND_H					// idk why it seems i can redefine rabbit.h to my hearts content!
#include "ssbtsound.h"
#endif
////

using namespace std;

#define BPM_TO_16BARS(x) (16 * 4 * (60.0 / (x))) //seconds per 16 bars
#define MAX_TOUCHES 	  7
#define FPS				 			30
#define BPM							145
#define PI							3.141592653589793238463
#define CENTERX					400	/* BUILT FOR 800x400 */
#define CENTERY					200

enum gesture { TAP_GESTURE, DISC_GESTURE, WEDGE_GESTURE, INVALID_GESTURE };
typedef enum gesture gesture_t;

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

	Touch touches[MAX_TOUCHES];				// stores touches as they come in...you may have a quantity of MAX_TOUCHES for one finger...
	Touch fingers[MAX_TOUCHES];				// stores each finger instead of storing the latest touch events that come in
																		// doing it this way allows us to reject input from more than 3 fingers
																		// also it allows us to recognize swipes...that's why we'll do 2 Touch arrays
  Rabbit AllRabbits[TOTALRABBITS];
	User User1;

	// todo: private
	ALLEGRO_DISPLAY *display;
  ALLEGRO_TIMER *timer;
	ALLEGRO_TIMER *metronome;
	ALLEGRO_EVENT_QUEUE *queue;
	ALLEGRO_EVENT event;
	ALLEGRO_DISPLAY_MODE disp_data;
	Ssbtsound ssbtsound;
	int num_touches;
  bool background;
	bool quit;
	bool accept_more_touches;
	bool gesture_processed;
	int measureNumber;

  int initAllegro5(void);
  void initAllRabbits(void);
	void timerLoop(void);
	int touch_main(void);
	void ctrlcHandler(int);

	void messAround(void);

	void draw_touches(int num, Touch touches[]);
	int which_finger(int id, int num, Touch touches[]);
	void printTouches(void);

	gesture_t id_gesture(void);

private:
	Application& getApplication(void);
	gesture_t currentGesture;
	struct sigaction sigIntHandler;

};

#endif
