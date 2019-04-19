#include <iostream>
#include "user.h"
#include "rabbit.h"
#include "constants.h"
using namespace std;

User::User(){
   truex = CENTERX;
   truey = CENTERY;
}

User::~User(){}

void User::setTrueX(int a){
	truex = a;
}

void User::setTrueY(int a){
	truey = a;
}

void User::teleport(int x, int y){
	setTrueX(x);
	setTrueY(y);
}

int User::getTrueX(){
	return truex;
}

int User::getTrueY(){
	return truey;
}

void User::activateInsideRabbits(Rabbit AllRabbits[]){
  // User has no disc or wedge
  if(!Disc1.isActivated() && !Wedge1.isActivated()){
    for (int i = 0; i<NUMRABBITS; i++){
      AllRabbits[i].activate(true);
    }
  }

  // User has a disc, check for wedge later
  if(Disc1.isActivated()){
  	for(int i=0;i<NUMRABBITS;i++){
  		if(AllRabbits[i].getDistanceToCenter() > getDisc1().getRadius1()
  		&& AllRabbits[i].getDistanceToCenter() < getDisc1().getRadius2()){
  			AllRabbits[i].activate(true);
  		}else{
  			AllRabbits[i].activate(false);
  		}
  	}
  }

  // User has a wedge
  if(Wedge1.isActivated()){
    for(int i=0;i<NUMRABBITS;i++){
      if(AllRabbits[i].getAngleToCenter() > getWedge1().getAngle1()
      && AllRabbits[i].getAngleToCenter() < getWedge1().getAngle2()){
        AllRabbits[i].activate(true);
      }else{
        AllRabbits[i].activate(false);
      }
    }
  }else{
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
	if(a < b){
		radius1 = a;
		radius2 = b;
	}else{
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
	if(a < b){
		angle1 = a;
		angle2 = b;
	}else{
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
