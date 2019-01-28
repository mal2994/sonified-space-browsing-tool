#include <iostream>
#include <cmath>
#include "rabbit.h"

using namespace std;

// CONSTRUCTOR
Rabbit::Rabbit()
{
    truex = 0;
   	truey = 0;
   	distance_to_user = 9999;
   	activated = false;
}

// MODIFICATION MEMBER FUNCTIONS
void Rabbit::setTrueX(int a)
{
	truex = a;
}

void Rabbit::setTrueY(int a)
{
	truey = a;
}

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