#include <iostream>
#include <stdlib.h>	//is this cpp?
#include "rabbit.h"
#include "user.h"

using namespace std;

int main(void)
{
	// user teleport
	User User1;
	cout << "User Initialized." << endl;
	cout << "coords: " << User1.getTrueX() << ", " << User1.getTrueY() << endl;
	User1.setTrueX(5);
	User1.setTrueY(10);
	cout << "User teleported." << endl;
	cout << "coords: " << User1.getTrueX() << ", " << User1.getTrueY() << endl;

	// rabbit create
	Rabbit Rabbit1;
	Rabbit1.setTrueX(10);
	Rabbit1.setTrueY(20);
	Rabbit1.calcDistanceToUser(User1.getTrueX(), User1.getTrueY());
	cout << "Rabbit1 Initialized." << endl;
	cout << "coords: " << Rabbit1.getTrueX() << ", " << Rabbit1.getTrueY() << endl;
	cout << "distance to user: " << Rabbit1.getDistanceToUser() << endl;


	return 0;
}