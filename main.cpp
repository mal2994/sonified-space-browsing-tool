#include "application.h"
#include <allegro5/allegro.h>
#include <thread>
#include <iostream>

using namespace std;

int main()
{
	int error = 0;

	Application *application = new Application();
	error = application->initAllegro5(); /* todo options to turn on allegro 5, csound */
	if(!error)
		application->touch_main();

	cout << "finished" << "\n";
	return 0;
}
