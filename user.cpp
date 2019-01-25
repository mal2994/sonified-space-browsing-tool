#include <iostream>
#include "user.h"
#include "rabbit.h"

using namespace std;

/* CONSTRUCTOR */
User::User()
{
    truex = 0;
   	truey = 0;
}

/* MODIFICATION MEMBER FUNCTIONS */
void User::setTrueX(int a)
{
	truex = a;
}

void User::setTrueY(int a)
{
	truey = a;
}

/* CONSTANT MEMBER FUNCTIONS */
int User::getTrueX()
{
	return truex;
}

int User::getTrueY()
{
	return truey;
}

void User::activateInsideRabbits(Rabbit AllRabbits[])
{
	// algorithm coming soon
	AllRabbits[0].activate(true);
}

Disc User::getDisc1()
{
	return Disc1;
}

Disc::Disc()
{
	radius1 = 0;
	radius2 = 0;
	activated = 0;
}

void Disc::activate(bool flag)
{
	activated = flag;
}

void Disc::setRadius1(int a)
{
	radius1 = a;
}

void Disc::setRadius2(int a)
{
	radius2 = a;
}

int Disc::getRadius1()
{
	return radius1;
}

int Disc::getRadius2()
{
	return radius2;
}

bool Disc::isActivated()
{
	return activated;
}
