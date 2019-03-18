// todo hrtf
#include "application.h"
#include <allegro5/allegro.h>
#include <iostream>
#include <stdio.h> // for sscanf()

using namespace std;

int main(int argc, char** argv) {
	int error = 0, param = 0;
	bool valid = true;
	Application *application = new Application();

	if(argc == 2){
		valid = sscanf(argv[1],"%d",&param);
		if(valid) valid = application->convertArgv1(param);
		else cout << "invalid\n";
		if(valid) application->setMode();		// set io mode with command line args
		else if (valid == false){
			application->askMode();							// ask for io mode if no command line args
			application->setMode();							// then set io mode
		}
		cout << "---------------------------------------------------------------\n";
		cout << "START PROGRAM? (y/n) ";
		cin >> param; //any variable that wont be used again, its just a wait
		if(param == 'n'){ exit(0);
		cout << "---------------------------------------------------------------\n";
		}
	}else if (argc == 1){
		application->modesDefault();
	}

	error = application->initAllegro5();
	if(!error)
		application->touch_main();

	cout << "finished" << "\n";
	return 0;
}
