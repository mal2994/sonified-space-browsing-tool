/*#include <iostream>
#include <cstdlib>
#include "rabbit.h"
#include "user.h"
#include "touch.h"*/
#include "application.h"
#include <allegro5/allegro.h>

using namespace std;

int main()
{
    Application *application = new Application();
    application->init();
    application->createWindow(30.0, 640, 480);
    application->appLoop();

    return 0;
}

/*int appLoop(void)
{
	//create user
	User User1;
	cout << "User Created." << "\n";
	cout << "coords: " << User1.getTrueX() << ", " << User1.getTrueY() << "\n";

	//create rabbits
	Rabbit AllRabbits[TOTALRABBITS];

	// user teleport
	User1.setTrueX(5);
	User1.setTrueY(10);
	cout << "User teleported." << "\n";
	cout << "coords: " << User1.getTrueX() << ", " << User1.getTrueY() << "\n";

	// new rabbit
	AllRabbits[0].setTrueX(5);
	AllRabbits[0].setTrueY(5);
	AllRabbits[0].calcDistanceToUser(User1.getTrueX(), User1.getTrueY());
	cout << "AllRabbits[0] Created." << "\n";
	cout << "coords: " << AllRabbits[0].getTrueX() << ", " << AllRabbits[0].getTrueY() << "\n";
	cout << "distance to user: " << AllRabbits[0].getDistanceToUser() << "\n";

	// create disc
	User1.getDisc1().activate(true);
	User1.getDisc1().setRadii(8,2);
	cout << "Disc created." << "\n";
	cout << "radius1: " << User1.getDisc1().getRadius1() << "\n";
	cout << "radius2: " << User1.getDisc1().getRadius2() << "\n";
	cout << "activated: " << User1.getDisc1().isActivated() << "\n";
	// activate (included in creating a disc)
	cout << "AllRabbits[0] activated? " << AllRabbits[0].isActivated() << "\n";
	User1.activateInsideRabbits(AllRabbits);
	cout << "AllRabbits[0] activated? " << AllRabbits[0].isActivated() << "\n";

	//wait for touch
	while(1)
	{
		touch_main();
	}
	return 0;
}*/
