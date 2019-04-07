// some keywords to search for when making new patches: TODO, CHANGE, MOVED, or just /*
#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <signal.h>		// for sigaction
#include <unistd.h>		// for sigaction
#include <allegro5/allegro.h>
#include "rabbit.h"
#include "user.h"
#include "ssbtgpio.h"
#include <thread>	// for threads 

#ifndef SSBTSOUND_H					// idk why it seems i can redefine rabbit.h to my hearts content! by the way, pragma once takes care of this
#include "ssbtsound.h"
#endif

using namespace std;
																								// you can replace all uses of BPM_TO_16BARS
#define BPM_TO_8BARS(x) (8 * 4 * (60.0 / (x)))	// with this to half the display flip time.
																								// you'll end up entering on the 9th bar on the next progression
																								// so be sure to change the drumackwav .wav file to the 8bar version
#define BPM_TO_16BARS(x) (16 * 4 * (60.0 / (x)))	// seconds per 16 bars. 64 (= 16*4) times Beats Per Second.
#define MAX_TOUCHES 	  7
#define FPS				 			1										// controls graphics and sound (ie rabbit teleport) updates
#define BPM							145									// 145bpm -> 0.41379bps -> 2.41666 spb -> 26.48275 seconds per progression
#define SCREENW					800
#define SCREENH					400
#define CENTERX					SCREENW/2
#define CENTERY					SCREENH/2
#define EAR_DIST				100
#define GEST_ANGLE_STY	20 // degrees 					// sensitivity for gestures
#define GEST_RADII_STY	20 // pixels 						// sensitivity for gestures, note that we will have to match the touch screen here. fingers too close start to become one.
#define CENTR_STY				50											// this is a plus or minus value so it ends up being 100
#define NEARSIGHTEDNESS 0.2                 		// sound is emitted how far across the screen? number is proportion of screen
#define SCREENDIAGONAL(x,y) sqrt(x*x + y*y)
#define DEGTORAD(x)					(x * 180 / ALLEGRO_PI)
// mode flag indices in mode_flags array
//#define DUMMY					0
//#define DUMMY					1
#define R2R_FLAG			2
#define STEREO_FLAG		3
#define SUR51_FLAG		4
#define SUR71_FLAG		5
#define TOUCH_FLAG		6
#define HRTF_FLAG			7

enum gesture { TAP_GESTURE, DISC_GESTURE, WEDGE_GESTURE, INVALID_GESTURE, NO_GESTURE };
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

	Touch touches[MAX_TOUCHES];				// stores the latest MAX_TOUCHES coordinates of latest fingers (can fill entire array with one finger swipe)
	Touch fingers[MAX_TOUCHES];				// stores one coordinate per MAX_TOUCHES fingers
  Rabbit AllRabbits[NUMRABBITS];
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
	int num_fingers;
  bool background;
	bool quit;
	bool accept_more_touches;
	bool gesture_identified;
	int measureNumber;

  int initAllegro5(void);
  void initAllRabbits(void);
	void timerLoop(void);
	int touch_main(void);
	void ctrlcHandler(int);
	void calculateChannels(void);

	void messAround(void);

	void draw_touches(int num, Touch touches[]);
	int which_finger(int id, int num, Touch touches[]);
	void printTouches(void);
	void modesDefault(void);

	gesture_t id_gesture(void);
	void draw_gesture(void);

	bool mode_flags[8]= {false, false, false, false, false, false, false, false};
	bool convertArgv1(int);
	void echoMode();
	void askMode();

	void ssbtgpiof(void);
	thread makeThread(void);
	
private:
	Application& getApplication(void);
	gesture_t currentGesture;
	struct sigaction sigIntHandler;
	int r2rdistances[NUMRABBITS-1] = {};
	int song;
	bool fpsready;
	//pthread_t gpiot;
	thread gpiot;
	SSBTGPIO ssbtgpio;
};

#endif
