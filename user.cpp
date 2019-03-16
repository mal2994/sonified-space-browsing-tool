#include <iostream>
#include "user.h"
#include "rabbit.h"
//#include "ssbtsound.h" //never tried this 

using namespace std;

// Constructor
User::User(){
   truex = 400;
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

void User::teleport(Ssbtsound& ssbtsound, Rabbit AllRabbits[], int x, int y){
  // modify user class attributes
	setTrueX(x);
	setTrueY(y);
	cout << "User teleported." << "\n";
	cout << "coords: " << getTrueX() << ", " << getTrueY() << "\n";

  // print some rabbit class attributes (hm they must already to be set todo are they?)
  AllRabbits[0].calcDistanceToUser(truex, truey);                           // does distance and distance complement
  AllRabbits[0].calcAngleToUser(truex, truey);

  // modify ssbtsound class attributes with data from rabbit class attributes
  ssbtsound.setDistanceChn(0,AllRabbits[0].getDistanceComplement());
  ssbtsound.setAngleChn(0,AllRabbits[0].getAngleToUser());
  /*ssbtsound.r0distance = AllRabbits[0].getDistanceComplement();
  cout << "r0distance = " << ssbtsound.r0distance <<"\n";
  ssbtsound.csound->SetChannel("r0distance", ssbtsound.r0distance);         // pass complement of distance as float to csound for amplitude adjustment
  ssbtsound.r0angle = AllRabbits[0].getAngleToUser();
  cout << "r0angle = " << ssbtsound.r0angle << "\n";
  ssbtsound.csound->SetChannel("r0angle", AllRabbits[0].getAngleToUser());*/
}

/* CONSTANT MEMBER FUNCTIONS */
int User::getTrueX(){
	return truex;
}

int User::getTrueY(){
	return truey;
}

void User::activateInsideRabbits(Rabbit AllRabbits[]){
  // User has no disc or wedge
//  if(!Disc1.activated && !Wedge1.activated){
  if(!Disc1.isActivated() && !Wedge1.isActivated()){
    for (int i = 0; i<NUMRABBITS; i++){
      AllRabbits[i].activate(true);
    }
  }

  // User has a disc, check for wedge later
  if(Disc1.isActivated()){
  	for(int i=0;i<NUMRABBITS;i++){
  		if(AllRabbits[i].getDistanceToUser() > getDisc1().getRadius1()
  		&& AllRabbits[i].getDistanceToUser() < getDisc1().getRadius2()){
  			AllRabbits[i].activate(true);
  		}else{
  			AllRabbits[i].activate(false);
  		}
  	}
  }

  // User has a wedge
  if(Wedge1.isActivated()){
    for(int i=0;i<NUMRABBITS;i++){
      if(AllRabbits[i].getAngleToUser() > getWedge1().getAngle1()
      && AllRabbits[i].getAngleToUser() < getWedge1().getAngle2()){
        AllRabbits[i].activate(true);
      }else{
        AllRabbits[i].activate(false);
      }
    }
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
