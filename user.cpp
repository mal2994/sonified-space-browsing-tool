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

void User::teleport(int x, int y){
	setTrueX(x);
	setTrueY(y);
	cout << "User teleported." << "\n";
	cout << "coords: " << getTrueX() << ", " << getTrueY() << "\n";
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

	// todo if disc not activated, activate all rabbits
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

Wedge& User::getWedge1()
{
	return Wedge1;
}

Wedge::Wedge()
{
	angle1 = -1;	//smaller radius
	angle2 = -1;	//bigger radius
	activated = 0;
}

Wedge::~Wedge(){}

void Wedge::activate(bool flag)
{
	activated = flag;
}

void Wedge::setAngle1(int a)
{
	angle1 = a;
}

void Wedge::setAngle2(int a)
{
	angle2 = a;
}

void Wedge::setAngles(int a, int b)
{
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

int Wedge::getAngle1()
{
	return angle1;
}

int Wedge::getAngle2()
{
	return angle2;
}

bool Wedge::isActivated()
{
	return activated;
}


