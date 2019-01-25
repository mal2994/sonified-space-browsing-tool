#ifndef USER_H
#define USER_H
#include "rabbit.h"

class Disc {
public:
   Disc();

   /* MODIFICATION MEMBER FUNCTIONS */
   void setRadius1(int);
   void setRadius2(int);
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
   //~User();

   /* MODIFICATION MEMBER FUNCTIONS */
   void setTrueX(int);
   void setTrueY(int);

   /* CONSTANT MEMBER FUNCTIONS */
   int getTrueX();
   int getTrueY();
   Disc getDisc1();
   void activateInsideRabbits(Rabbit[]); //formerly known as muteRabbits() in the specification document.

private:
   int truex;
   int truey;
   Disc Disc1;
};

#endif