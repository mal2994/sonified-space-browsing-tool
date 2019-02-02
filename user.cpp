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
// DESTRUCTOR
User::~User(){}

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
	//AllRabbits[0].activate(true);

	
	//disc
	for(int i=0;i<TOTALRABBITS;i++)
	{
		if(AllRabbits[i].getDistanceToUser() > getDisc1().getRadius1()
		&& AllRabbits[i].getDistanceToUser() < getDisc1().getRadius2())
		{
			AllRabbits[i].activate(true);
		}
		else
		{
			AllRabbits[i].activate(false);
		}
	}
	
}

Disc& User::getDisc1()
{
	return Disc1;
}

Disc::Disc()
{
	radius1 = -1;	//smaller radius
	radius2 = -1;	//bigger radius
	activated = 0;
}

Disc::~Disc(){}

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

void Disc::setRadii(int a, int b)
{
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