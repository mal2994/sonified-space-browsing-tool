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

void Rabbit::calcDistanceToUser(int userx, int usery)
{
	distance_to_user = sqrt(pow(userx - truex, 2) + pow(usery - truey, 2)); //this is an integer, not a double. we are rounding.
}

void Rabbit::activate(bool flag)
{
	activated = flag;
}

// CONSTANT MEMBER FUNCTIONS
int Rabbit::getTrueX()
{
	return truex;
}

int Rabbit::getTrueY()
{
	return truey;
}

int Rabbit::getDistanceToUser() //be sure to call calcDistanceToUser() as appropriate
{
	return distance_to_user;
}

bool Rabbit::isActivated()
{
	return activated;
}

Rabbit& Rabbit::getRabbit()
{
	return *this;//Rabbit;
}