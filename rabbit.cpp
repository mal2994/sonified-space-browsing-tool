#include <iostream>
#include <cmath>
#include "rabbit.h"
#include "application.h"
#include "constants.h"
using namespace std;

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
void Rabbit::setRabbitId(int a){
  rabbit_id = a;
}

void Rabbit::setFox(bool a){
	is_fox = a;
}

void Rabbit::setTrueX(int x){
	truex = x;
}

void Rabbit::setTrueY(int y){
	truey = y;
}

void Rabbit::setTrueXandTrueY(int x, int y){
  setTrueX(x);
  setTrueY(y);
}

void Rabbit::initRabbit(int a, bool b, bool c, int x, int y, int userx, int usery){
  setTrueXandTrueY(x,y);
	calcDistanceToUser(userx, usery);
  rabbit_id = a;
  is_fox = b;
  is_rabbit = c;
}

void Rabbit::calcDistanceToUser(int userx, int usery){
	distance_to_user = abs(sqrt(pow(userx - truex, 2) + pow(usery - truey, 2))); // this is an integer, not a double. we are rounding.
	distance_complement = pow((((float)1) - ((distance_to_user/(SCREENDIAGONAL(SCREENW,SCREENH))))),2);   // complement distance to amplitude
}

void Rabbit::calcAngleToUser(int userx, int usery){
  angle_to_user = DEGTORAD(acos((userx - truex)/distance_to_user));     // get our adjacent and hypotenuse
  if(usery < truey) angle_to_user = (angle_to_user*-1)+360;             // reflection & offset to get an increasing value after cos 1/2
  angle_to_user -= 90;                                                  // 0 deg is to the left, we will make it to the up
  if(angle_to_user < 0) angle_to_user += 360;                           // ^ will give us some negatives, which are decreasing at a convenient rate...
  if(distance_to_user == 0) angle_to_user = 0;                          // todo activate all speakers or earcon or something
}

void Rabbit::calcDistanceToCenter(int userx, int usery){
	distance_to_center = abs(sqrt(pow(CENTERX - truex, 2) + pow(CENTERY - truey, 2)));
}

void Rabbit::calcAngleToCenter(int userx, int usery){
  angle_to_center = DEGTORAD(acos((CENTERX - truex)/distance_to_center));   // get our adjacent and hypotenuse
  if(CENTERY < truey) angle_to_center = (angle_to_center*-1)+360;           // reflection & offset to get an increasing value after cos 1/2
  angle_to_center -= 90;                                                    // 0 deg is to the left, we will make it to the up
  if(angle_to_center < 0) angle_to_center += 360;                           // ^ will give us some negatives, which are decreasing at a convenient rate...
  if(distance_to_center == 0) angle_to_center = 0;                          // todo activate all speakers or earcon or something
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
float Rabbit::getDistanceToUser(){
	return distance_to_user;
}
float Rabbit::getAngleToCenter(){
  return angle_to_center;
}
float Rabbit::getDistanceToCenter(){
	return distance_to_center;
}
float Rabbit::getDistanceComplement(){
	return distance_complement;
}
bool Rabbit::isActivated(){
	return activated;
}
bool Rabbit::isFox(){
  return is_fox;
}
Rabbit& Rabbit::getRabbit(){
	return *this;
}
