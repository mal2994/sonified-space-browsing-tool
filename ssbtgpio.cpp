#include "ssbtgpio.h"
#include <wiringPi.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

// Constructor
SSBTGPIO::SSBTGPIO(){
	infile.open("dummy.txt");
}
// Destructor
SSBTGPIO::~SSBTGPIO(){
	infile.close();
}

int SSBTGPIO::setUpPins(){
	if(wiringPiSetup() == -1) return -1;
	pinMode(MPLXR0, OUTPUT);
	pinMode(MPLXR1, OUTPUT);
	pinMode(MPLXR2, OUTPUT);
	pinMode(IN0, INPUT);
	pinMode(IN1, INPUT);
	pinMode(IN2, INPUT);
	pinMode(IN3, INPUT);
	pullUpDnControl(IN0, PUD_OFF);
	pullUpDnControl(IN1, PUD_OFF);
	pullUpDnControl(IN2, PUD_OFF);
	pullUpDnControl(IN3, PUD_OFF);
	return 0; // no error
}

int SSBTGPIO::readChn(int chn){					// request one of five channels from mux, return integer value of 4-bit read 0-15
	// select channel from multiplexer
	if(chn == 4){
		digitalWrite(MPLXR2,1);
		digitalWrite(MPLXR1,0);
		digitalWrite(MPLXR0,0);
	}else if(chn == 3){
		digitalWrite(MPLXR2,0);
		digitalWrite(MPLXR1,1);
		digitalWrite(MPLXR0,1);
	}else if(chn == 2){
		digitalWrite(MPLXR2,0);
		digitalWrite(MPLXR1,1);
		digitalWrite(MPLXR0,0);
	}else if(chn == 1){
		digitalWrite(MPLXR2,0);
		digitalWrite(MPLXR1,0);
		digitalWrite(MPLXR0,1);
	}else if(chn == 0){
		digitalWrite(MPLXR2,0);
		digitalWrite(MPLXR1,0);
		digitalWrite(MPLXR0,0);
	}

	// read from gpio pins
	delay(100);
	int val0 = digitalRead(IN0);
	int val1 = digitalRead(IN1);
	int val2 = digitalRead(IN2);
	int val3 = digitalRead(IN3);

	// convert 4-bit binary to decimal integer
	int ret = (1*val0) + (2*val1) + (4*val2) + (8*val3);
	return ret;
}

int SSBTGPIO::getPoint1(){
	return point1;
}

int SSBTGPIO::getPoint2(){
	return point2;
}

int SSBTGPIO::readFile(){
	cout << "reading from file...\n";
  if (infile){
    string s;
    if (getline( infile, s )){
      istringstream ss( s );
      if (ss){
        string s;
        if (getline( ss, s, ',' )) point1 = stoi(s);
        if (getline( ss, s, ',' )) point2 = stoi(s);
      }
    }else return 1; // finished file
  }else return -1;  // file read error
  return 0;     // got one line fine
}

/*int main(){
	SSBTGPIO ssbtgpio;
	int val = 0;
	if(ssbtgpio.setUpPins() == 1){
		return -1;
	}
	while(1){
		val = ssbtgpio.readChn(0);
		delay(400);
		cout << "chn0 = " << val << "\n";
	}
}*/
