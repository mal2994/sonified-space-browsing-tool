#include <iostream>
#include <cmath>
#include "rabbit.h"

using namespace std;

// CONSTRUCTOR
Rabbit::Rabbit()
{
   rabbit_id = 0;
   truex = -100;
   truey = -100;
   distance_to_user = 9999;
   distance_complement = 0.0;
   angle_to_user = 0.0;
   activated = false;
	 is_fox = false;
   is_rabbit = false;
}

Rabbit::~Rabbit(){}

// MODIFICATION MEMBER FUNCTIONS
void Rabbit::setTrueX(int x){
	truex = x;
}

void Rabbit::setTrueY(int y){
	truey = y;
}

void Rabbit::setTrueXandTrueY(int x, int y){  // aka teleport todo 
  setTrueX(x);
  setTrueY(y);
//  cout << "Rabbit coordinates: ("<<x<<","<<y<<") \n";
}

void Rabbit::initRabbit(int a, bool b, bool c, int x, int y, int userx, int usery){ // a= rabbit_id, b=is_fox, c=is_rabbit, x=truex, y=truey, userx, usery
  setTrueXandTrueY(x,y);
	calcDistanceToUser(userx, usery);
  rabbit_id = a; // never change
  is_fox = b; //no set function because this should never change
  is_rabbit = c; // also should never change
//	cout << "Rabbit created." << "\n";
}

void Rabbit::calcDistanceToUser(int userx, int usery){
	distance_to_user = sqrt(pow(userx - truex, 2) + pow(usery - truey, 2));             //this is an integer, not a double. we are rounding.
  distance_complement = ((float)1 - (distance_to_user/900));     // complement distance to amplitude
//  cout << "Rabbit["<<rabbit_id<<"] distance to user: " << distance_to_user << ", complement is " << distance_complement << "\n";
}

void Rabbit::calcAngleToUser(int userx, int usery){
  angle_to_user = acos((abs(truex - userx)/distance_to_user))*(180.0/3.141592653589793238463);
//  cout << "Rabbit["<<rabbit_id<<"] angle to user: " << angle_to_user << "\n";
}

void Rabbit::activate(bool flag){
	activated = flag;
}

// CONSTANT MEMBER FUNCTIONS
int Rabbit::getTrueX(){
	return truex;
}

int Rabbit::getTrueY(){
	return truey;
}

int Rabbit::getRabbitId(){
  return rabbit_id;
}

float Rabbit::getAngleToUser(){
  return angle_to_user;
}

float Rabbit::getDistanceToUser(){ //be sure to call calcDistanceToUser() as appropriate{
	return distance_to_user;
}

float Rabbit::getDistanceComplement(){ //be sure to call calcDistanceToUser() as appropriate{
	return distance_complement;
}

bool Rabbit::isActivated(){
	return activated;
}

Rabbit& Rabbit::getRabbit(){
	return *this;
}
