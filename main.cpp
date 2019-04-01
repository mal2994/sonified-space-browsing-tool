// todo hrtf
#include "application.h"
#include <allegro5/allegro.h>
#include <iostream>
#include <stdio.h> // for sscanf()

using namespace std;

int main(int argc, char** argv) {
	int error = 0, param = 0;
	char yn = 'n';
	bool valid = true;
	Application *application = new Application();

	if(argc == 2){												// if one parameter given from command line like so: ./ssbt 11100111
		valid = sscanf(argv[1],"%d",&param);
		if(valid) valid = application->convertArgv1(param);		// char array to int, reuse valid variable
		else cout << "invalid\n";
		if(valid) application->echoMode();						// set io mode with command line args
		else if (valid == false){
			application->askMode();							// ask for io mode if no command line args
			application->echoMode();						// then echo it back to users
		}
		cout << "---------------------------------------------------------------\n";
		cout << "Enter commands by first pressing the up arrow then type one of\n";
		cout << "the following commands:\n";
//		cout << "one letter for action, and three digits for coordinates\n";
//		cout << "disc and wedge require two points, teleport only one point\n";
		cout << "teleport: txxxyyy\n";
		cout << "disc: dxxxyyyxxxyyy\n";
		cout << "wedge wxxxyyyxxxyyy\n";
		cout << "START PROGRAM? (y/n) ";
		cin >> yn; //any variable that wont be used again, its just a wait
		if(yn == 'n'){
			cout << "---------------------------------------------------------------\n";
			exit(0);
		}
	}else if (argc == 1){										// no additional parameters like so: ./ssbt
		application->modesDefault();
	}

	error = application->initAllegro5();		// using mode_flags from either askMode() or modesDefault()
	if(!error)
		application->touch_main();						// start the program

	cout << "finished" << "\n";
	return 0;
}
