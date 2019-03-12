#include <iostream>
#include <cmath>
#include "rabbit.h"

using namespace std;

// CONSTRUCTOR
Rabbit::Rabbit()
{
   truex = -100;
   truey = -100;
   distance_to_user = 9999;
   distance_complement = 0.0;
   angle_to_user = 0.0;
   activated = false;
	 is_fox = false;
}

Rabbit::~Rabbit(){}

// MODIFICATION MEMBER FUNCTIONS
void Rabbit::setTrueX(int a)
{
	truex = a;
}

void Rabbit::setTrueY(int a)
{
	truey = a;
}

/*this in apploop for now
void Rabbit::initRabbit(int x, int y){
	AllRabbits[0].setTrueX(5);
	AllRabbits[0].setTrueY(5);
	AllRabbits[0].calcDistanceToUser(User1.getTrueX(), User1.getTrueY());
	cout << "AllRabbits[0] Created." << "\n";
	cout << "coords: " << AllRabbits[0].getTrueX() << ", " << AllRabbits[0].getTrueY() << "\n";
	cout << "distance to user: " << AllRabbits[0].getDistanceToUser() << "\n";
}*/

void Rabbit::calcDistanceToUser(int userx, int usery){
	distance_to_user    = sqrt(pow(userx - truex, 2) + pow(usery - truey, 2));             //this is an integer, not a double. we are rounding.
  distance_complement = ((float)1 - (distance_to_user/900));     // complement distance to amplitude
}

void Rabbit::calcAngleToUser(int userx, int usery){
  angle_to_user = acos((abs(truex - userx)/distance_to_user))*(180.0/3.141592653589793238463);
}

float Rabbit::getAngleToUser(){
  return angle_to_user;
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
	return *this;//Rabbit;
}
