#ifndef RABBIT_H
#define RABBIT_H

#define TOTALRABBITS  4       // array size   // todo doesnt seem to be used...reasonably so
#define NUMRABBITS    4       // total used

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
   int getRabbitId();
   float getDistanceToUser();
   float getDistanceComplement();
   float getAngleToUser();
   bool isActivated();
   bool isFox();
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
