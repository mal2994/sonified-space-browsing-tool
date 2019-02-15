#ifndef USER_H
#define USER_H
#include "rabbit.h"

class Wedge {
public:
	Wedge();
	~Wedge();
	/* MODIFICATION MEMBER FUNCTIONS */
	void setAngle1(int);
	void setAngle2(int);
	void setAngles(int, int);
	void activate(bool);
	/* CONSTANT MEMBER FUNCTIONS */   
   int getAngle1();
   int getAngle2();
   bool isActivated();
private:
	int angle1;
	int angle2;
	bool activated;
};


class Disc {
public:
   Disc();
	~Disc();
   /* MODIFICATION MEMBER FUNCTIONS */
   void setRadius1(int);
   void setRadius2(int);
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
	void teleport(int, int);

   /* CONSTANT MEMBER FUNCTIONS */
   int getTrueX();
   int getTrueY();
   Disc& getDisc1();
   Wedge& getWedge1();
   void activateInsideRabbits(Rabbit[]); //formerly known as muteRabbits() in the specification document.

private:
   int truex;
   int truey;
   Disc Disc1;
   Wedge Wedge1;
};

#endif
