#ifndef USER_H
#define USER_H

//#include "application.h"
#include "constants.h"
#include "rabbit.h"

#ifndef SSBTSOUND_H					// idk why it seems i can redefine rabbit.h to my hearts content!
#include "ssbtsound.h"
#endif

//#include "application.h"

class Wedge {
public:
	Wedge();
	~Wedge();
	/* MODIFICATION MEMBER FUNCTIONS */
	void setAngles(int, int);							// set both angles at same time so the small one goes in angle1
	void activate(bool);
	/* CONSTANT MEMBER FUNCTIONS */
   int getAngle1();
   int getAngle2();
   bool isActivated();
private:
	int angle1;														// the small one 0-359 (TODO techincally these are azimuths...)
	int angle2;														// the big one 0-359
	bool activated;
};


class Disc {
public:
   Disc();
	~Disc();
   /* MODIFICATION MEMBER FUNCTIONS */
   void setRadii(int, int);
   void activate(bool);

   /* CONSTANT MEMBER FUNCTIONS */
   int getRadius1();
   int getRadius2();
   bool isActivated();

private:
   int radius1;
   int radius2;
   bool activated;
};

class User {
public:
   User();
   ~User();

   /* MODIFICATION MEMBER FUNCTIONS */
   void setTrueX(int);
   void setTrueY(int);
	 void teleport(int, int);		// fun fact arrays are passed by pointer by default

   /* CONSTANT MEMBER FUNCTIONS */
   int getTrueX();
   int getTrueY();
   Disc& getDisc1();
   Wedge& getWedge1();
   void activateInsideRabbits(Rabbit[]); // formerly known as muteRabbits() in the specification document.

private:
   int truex;
   int truey;
   Disc Disc1;
   Wedge Wedge1;
};

#endif
