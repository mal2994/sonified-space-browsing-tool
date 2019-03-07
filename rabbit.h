#ifndef RABBIT_H
#define RABBIT_H

#define TOTALRABBITS 10

class Rabbit {
public:
   // CONSTRUCTOR & DESTRUCTOR
   Rabbit();
   ~Rabbit();

   // MODIFICATION MEMBER FUNCTIONS mutators
   void setTrueX(int);
   void setTrueY(int);
   void calcDistanceToUser(int, int);
   void activate(bool);

   // CONSTANT MEMBER FUNCTIONS accessors
   int getTrueX();
   int getTrueY();
   float getDistanceToUser();
   bool isActivated();
   Rabbit& getRabbit();

private:
   int truex;
   int truey;
   ;int distance_to_user;
   float distance_to_user;
   bool activated;
	bool is_fox;
};



#endif
