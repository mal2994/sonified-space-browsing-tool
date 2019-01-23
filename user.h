#ifndef USER_H
#define USER_H

class User {
public:
   // CONSTRUCTOR & DESTRUCTOR
   User();
   //~User();

   // MODIFICATION MEMBER FUNCTIONS
   void setTrueX(int);
   void setTrueY(int);

   // CONSTANT MEMBER FUNCTIONS
   int getTrueX();
   int getTrueY();

private:
   int truex;
   int truey;

};



#endif