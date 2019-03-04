#include "application.h"
#include <allegro5/allegro.h>
#include <thread>
#include <iostream>

using namespace std;

int main()
{
	int error = 0;
	
   Application *application = new Application();
   error = application->init();
	if(!error)
		application->appLoop();
	
	cout << "finished" << "\n";
	
	
   return 0;
}
