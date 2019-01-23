#include <iostream>
#include "user.h"

using namespace std;

// CONSTRUCTOR
User::User()
{
    truex = 0;
   	truey = 0;
}

// MODIFICATION MEMBER FUNCTIONS
void User::setTrueX(int a)
{
	truex = a;
}

void User::setTrueY(int a)
{
	truey = a;
}

// CONSTANT MEMBER FUNCTIONS
int User::getTrueX()
{
	return truex;
}

int User::getTrueY()
{
	return truey;
}
