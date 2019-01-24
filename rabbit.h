#ifndef RABBIT_H
#define RABBIT_H

class Rabbit {
public:
   // CONSTRUCTOR & DESTRUCTOR
   Rabbit();
   //~User();

   // MODIFICATION MEMBER FUNCTIONS
   void setTrueX(int);
   void setTrueY(int);
   void calcDistanceToUser(int, int);
   void activate(bool);

   // CONSTANT MEMBER FUNCTIONS
   int getTrueX();
   int getTrueY();
   int getDistanceToUser();
   bool isActivated();
//   Rabbit getRabbit();

private:
   int truex;
   int truey;
   int distance_to_user;
   bool activated;
};



#endif