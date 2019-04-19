#ifndef RABBIT_H
#define RABBIT_H

class Rabbit {
public:
   // CONSTRUCTOR & DESTRUCTOR
   Rabbit();
   ~Rabbit();

   // MODIFICATION MEMBER FUNCTIONS mutators
   void setRabbitId(int);
	 void setFox(bool);
   void setTrueX(int);
   void setTrueY(int);
   void setTrueXandTrueY(int, int);
   void calcDistanceToUser(int, int);
   void calcAngleToUser(int, int);
   void calcDistanceToCenter(int, int);
   void calcAngleToCenter(int,int);
   void activate(bool);
   void initRabbit(int, bool, bool, int, int, int, int);

   // CONSTANT MEMBER FUNCTIONS accessors
   int getTrueX();
   int getTrueY();
   int getRabbitId();
   float getDistanceToUser();
   float getDistanceComplement();
   float getDistanceToCenter();
   float getAngleToCenter();
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
   float distance_to_center;
   float angle_to_center;
   float angle_to_user;
   bool activated;
   bool is_rabbit;
	 bool is_fox;
};

#endif
