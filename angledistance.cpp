// g++ angledistance.cpp application.cpp application.h rabbit.h rabbit.cpp user.h user.cpp ssbtsound.cpp ssbtsound.h `pkg-config --libs allegro-5 allegro_primitives-5` -lcsound64 -lpthread -lcsnd6 -ocsPerfThreadExample -o unit --std=c++11
// move the user around the rabbit in a square-shaped fashion and print the values.
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <iomanip>				// for setw() and setprecision()
#include "rabbit.h"				// for rabbit class
#include "application.h"	// for SCREENDIAGONAL()
using namespace std;

int main(){
// initialize
	Rabbit AllRabbits[1];	// just make one rabbit for this test. the engine will make a user.
	int ux = 0, uy = 0;
	int testx[8] = {400,500,500,500,400,300,300,300};										// get some test points
	int testy[8] = {100,100,200,300,300,300,200,100};										// get some test points
	cout << "screen diagonal: " << ((float)SCREENDIAGONAL(SCREENW,SCREENH)) << "\n";
	cout << "maximum distance: " << ((float)SCREENDIAGONAL(SCREENW,SCREENH)/2) << "\n";
// loop through your test points
	for(int i = 0; i < 8; i++){
		ux = testx[i];
		uy = testy[i];
		AllRabbits[0].initRabbit(0, false, true, 400, 200, ux, uy);
		AllRabbits[0].activate(true);	// in production code, we are to use activateInsideRabbits()
		AllRabbits[0].calcDistanceToUser(ux,uy);
		AllRabbits[0].calcAngleToUser(ux,uy);
		cout << " rabbit angle: " << setw(3) << AllRabbits[0].getAngleToUser() << " ";
		cout << "user x: " << ux << " user y: " << uy;
		cout << setprecision(3);
		cout << " distance to user: " << AllRabbits[0].getDistanceToUser() << ", complement is " << setw(3) << AllRabbits[0].getDistanceComplement() << "\n";
	}
}
