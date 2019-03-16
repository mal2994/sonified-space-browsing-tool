#ifndef RABBIT_H
#define RABBIT_H

#define TOTALRABBITS  3       // array size
#define NUMRABBITS    3       // total used

class Rabbit {
public:
   // CONSTRUCTOR & DESTRUCTOR
   Rabbit();
   ~Rabbit();

   // MODIFICATION MEMBER FUNCTIONS mutators
   void setTrueX(int);
   void setTrueY(int);
   void setTrueXandTrueY(int, int);
   void calcDistanceToUser(int, int);
   void calcAngleToUser(int, int);
   void activate(bool);
   void initRabbit(int, bool, bool, int, int, int, int);

   // CONSTANT MEMBER FUNCTIONS accessors
   int getTrueX();
   int getTrueY();
   float getDistanceToUser();
   float getDistanceComplement();
   float getAngleToUser();
   bool isActivated();
   Rabbit& getRabbit();

private:
   int truex;
   int truey;
   int rabbit_id;
   float distance_to_user;
   float distance_complement;
   float angle_to_user;
   bool activated;
   bool is_rabbit;
	 bool is_fox;
};

#endif
