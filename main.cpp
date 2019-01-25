#include <iostream>
#include <stdlib.h>	//is this cpp?
#include "rabbit.h"
#include "user.h"

using namespace std;

int main(void)
{
	//create user
	User User1;
	cout << "User Created." << endl;
	cout << "coords: " << User1.getTrueX() << ", " << User1.getTrueY() << endl;

	//create rabbit array for the world
	Rabbit AllRabbits[10];

	// user teleport
	User1.setTrueX(5);
	User1.setTrueY(10);
	cout << "User teleported." << endl;
	cout << "coords: " << User1.getTrueX() << ", " << User1.getTrueY() << endl;

	// new rabbit
	Rabbit Rabbit1;
	AllRabbits[0] = Rabbit1;
	Rabbit1.setTrueX(10);
	Rabbit1.setTrueY(20);
	Rabbit1.calcDistanceToUser(User1.getTrueX(), User1.getTrueY());
	cout << "Rabbit1 Created." << endl;
	cout << "coords: " << Rabbit1.getTrueX() << ", " << Rabbit1.getTrueY() << endl;
	cout << "distance to user: " << Rabbit1.getDistanceToUser() << endl;

	// create disc
	User1.getDisc1().setRadius1(2);
	User1.getDisc1().setRadius2(8);
	User1.getDisc1().activate(true);
	cout << "Disc created." << endl;
	cout << "radius1: " << User1.getDisc1().getRadius1() << endl;
	cout << "radius2: " << User1.getDisc1().getRadius2() << endl;

	// activate Rabbit1
	User1.activateInsideRabbits(AllRabbits);
	cout << "Rabbit1 muted? " << Rabbit1.isActivated() << endl;

	return 0;
}