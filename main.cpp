#include "application.h"
#include <allegro5/allegro.h>
#include <thread>
#include <iostream>

using namespace std;

int main()
{
   Application *application = new Application();
   application->init();
   //application->createWindow(30.0, 640, 480);
	application->appLoop();
	//thread t1(application->appLoop);
	//thread t2(application->timerLoop);
	
//	t1.join();
//	t2.join();
	
	cout << "finished" << "\n";
	
	
   return 0;
}