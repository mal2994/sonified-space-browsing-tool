#ifndef CONSTANTS_H_
#define CONSTANTS_H_
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
#define SWISH_DIST			100 										// how close does user have to be to fox to get swish?
#define FOX_STY					100											// how close to fox_voltage does fox have to be to become fox?
#define GEST_ANGLE_STY	5 // degrees //both of these were 20 					// sensitivity for gestures
#define GEST_RADII_STY	5 // pixels 						// sensitivity for gestures, note that we will have to match the touch screen here. fingers too close start to become one.
#define CENTR_STY				50											// this is a plus or minus value so it ends up being 2x what you put here
#define NEARSIGHTEDNESS 0.2                 		// sound is emitted how far across the screen? number is proportion of screen NOT USED.
#define SCREENDIAGONAL(x,y) sqrt(x*x + y*y)
#define DEGTORAD(x)					(x * 180 / ALLEGRO_PI)

#define NUMSONGS 			2
#define NUMINSTR 			4
#define NUMRABBITS    1
// mode flag indices in mode_flags array
//#define DUMMY					0
#define GPIO_FLAG			1				// TODO this is not in the code!!
#define R2R_FLAG			2
#define STEREO_FLAG		3
#define SUR51_FLAG		4
#define SUR71_FLAG		5
#define TOUCH_FLAG		6
#define HRTF_FLAG			7

#endif
