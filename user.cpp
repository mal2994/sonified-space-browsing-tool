#include <iostream>
#include "user.h"
#include "rabbit.h"
//#include "ssbtsound.h" //never tried this

using namespace std;

// Constructor
User::User(){
   truex = 400;     //todo CENTERX CENTERY
   truey = 200;
}
// Destructor
User::~User(){}

// MODIFICATION MEMBER FUNCTIONS //
void User::setTrueX(int a){
	truex = a;
}

void User::setTrueY(int a){
	truey = a;
}

void User::teleport(int x, int y){
	setTrueX(x);
	setTrueY(y);
	cout << "User teleported." << "\n";
	cout << "coords: " << getTrueX() << ", " << getTrueY() << "\n";
}

/* CONSTANT MEMBER FUNCTIONS */
int User::getTrueX(){
	return truex;
}

int User::getTrueY(){
	return truey;
}

void User::activateInsideRabbits(Rabbit AllRabbits[]){
  cout << "user x: " <<truex<< " user y: "<<truey<<"\n";
  // User has no disc or wedge
  if(!Disc1.isActivated() && !Wedge1.isActivated()){
    for (int i = 0; i<NUMRABBITS; i++){
      AllRabbits[i].activate(true);
      cout << "[activateInsideRabbits] AllRabbits["<<i<<"] rabbit_id " << AllRabbits[i].getRabbitId() << " truex " << AllRabbits[i].getTrueX() << " truey " << AllRabbits[i].getTrueY() << " distance_to_user " << AllRabbits[i].getDistanceToUser() << " angle_to_user " << AllRabbits[i].getAngleToUser() << "\n";
    }
  }

  // User has a disc, check for wedge later
  else if(Disc1.isActivated()){
  	for(int i=0;i<NUMRABBITS;i++){
  		if(AllRabbits[i].getDistanceToUser() > getDisc1().getRadius1()
  		&& AllRabbits[i].getDistanceToUser() < getDisc1().getRadius2()){
  			AllRabbits[i].activate(true);
  		}else{
  			AllRabbits[i].activate(false);
  		}
      cout << "[activateInsideRabbits] AllRabbits["<<i<<"] rabbit_id " << AllRabbits[i].getRabbitId() << " truex " << AllRabbits[i].getTrueX() << " truey " << AllRabbits[i].getTrueY() << " distance_to_user " << AllRabbits[i].getDistanceToUser() << " angle_to_user " << AllRabbits[i].getAngleToUser() << "\n";
  	}
  }

  // User has a wedge
  else if(Wedge1.isActivated()){
    for(int i=0;i<NUMRABBITS;i++){
      if(AllRabbits[i].getAngleToUser() > getWedge1().getAngle1()
      && AllRabbits[i].getAngleToUser() < getWedge1().getAngle2()){
        AllRabbits[i].activate(true);
      }else{
        AllRabbits[i].activate(false);
      }
      cout << "[activateInsideRabbits] AllRabbits["<<i<<"] rabbit_id " << AllRabbits[i].getRabbitId() << " truex " << AllRabbits[i].getTrueX() << " truey " << AllRabbits[i].getTrueY() << " distance_to_user " << AllRabbits[i].getDistanceToUser() << " angle_to_user " << AllRabbits[i].getAngleToUser() << "\n";
    }
  }else{
    cout << "[activateInsideRabbits] you dont have a disc wedge or no disc wedge all that stuff.\n";
  }
}

Disc& User::getDisc1(){
	return Disc1;
}

Disc::Disc(){
	radius1 = -1;	//smaller radius
	radius2 = -1;	//bigger radius
	activated = 0;
}

Disc::~Disc(){}

void Disc::activate(bool flag){
	activated = flag;
}

void Disc::setRadii(int a, int b){
	if(a < b)
	{
//		cout << "a<b" << endl;
		radius1 = a;
		radius2 = b;
	}else
	{
//		cout << "a>b" << endl;
		radius1 = b;
		radius2 = a;
	}
}

int Disc::getRadius1(){
	return radius1;
}

int Disc::getRadius2(){
	return radius2;
}

bool Disc::isActivated(){
	return activated;
}

Wedge& User::getWedge1(){
	return Wedge1;
}

Wedge::Wedge(){
	angle1 = -1;	//smaller angle
	angle2 = -1;	//bigger angle
	activated = 0;
}

Wedge::~Wedge(){}

void Wedge::activate(bool flag){
	activated = flag;
}

void Wedge::setAngles(int a, int b){
	if(a < b)
	{
//		cout << "a<b" << endl;
		angle1 = a;
		angle2 = b;
	}else
	{
//		cout << "a>b" << endl;
		angle1 = b;
		angle2 = a;
	}
}

int Wedge::getAngle1(){
	return angle1;
}

int Wedge::getAngle2(){
	return angle2;
}

bool Wedge::isActivated(){
	return activated;
}
