#ifndef APPLICATION_H_
#define APPLICATION_H_
#include <signal.h>		// for sigaction
#include <unistd.h>		// for sigaction
#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include "rabbit.h"
#include "user.h"
#include "ssbtgpio.h"
#include "constants.h"
#include <thread>
#ifndef SSBTSOUND_H
#include "ssbtsound.h"
#endif
using namespace std;

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

	Touch touches[MAX_TOUCHES];
	Touch fingers[MAX_TOUCHES];
  Rabbit AllRabbits[NUMRABBITS];
	User User1;

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
	void rotateRabbits(void);
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
	void calcFoxFound(void);
	ALLEGRO_FONT * font;
	Application& getApplication(void);
	SSBTGPIO ssbtgpio;

private:
	gesture_t currentGesture;
	struct sigaction sigIntHandler;
	int r2rdistances[NUMRABBITS-1] = {};
	int song;
	int fox_voltage;
	thread gpiot;
	void isrwrapper(void);
	bool found_fox;
	bool draw_found;
	bool draw_file_complete;
};

#endif
