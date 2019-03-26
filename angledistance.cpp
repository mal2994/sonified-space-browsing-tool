/*top right			- front right & center	-	25
bottom right	-	front right						- 331
bottom left		-  											- 26
																			- 24
																			*/
#include <iostream>
#include <stdio.h>
#include <cmath>
#include "rabbit.h"
#include "application.h"
using namespace std;
int main()
{
	Rabbit AllRabbits[1];
	int ux = 0, uy = 0;
		cout << "user x: " << ux << "\n";
		cout << "user y: " << uy << "\n";
	while(1){
		AllRabbits[0].initRabbit(0, false, true, 200, 400, ux, uy);
		AllRabbits[0].calcDistanceToUser(ux,uy);
		AllRabbits[0].calcAngleToUser(ux,uy);
		cout << "rabbit distance: " << AllRabbits[0].getDistanceToUser() << "\n";
		cout << "rabbit angle: " << AllRabbits[0].getAngleToUser() << "\n";
		cout << "user x: ";
		cin >> ux;
		cout << "user y: ";
		cin >> uy;
	}
}
