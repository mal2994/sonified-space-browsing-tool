#include "ssbtgpio.h"
#include <wiringPi.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm> // for count()
using namespace std;

SSBTGPIO::SSBTGPIO(){
	datafile.open("dummy.txt");
	lines_done = 0;
}

SSBTGPIO::~SSBTGPIO(){
	datafile.close();
}

int SSBTGPIO::setUpPins(){
	if(wiringPiSetup() == -1) return -1;
	pinMode(MPLXR0, OUTPUT);
	pinMode(MPLXR1, OUTPUT);
	pinMode(IN0, INPUT);
	pinMode(IN1, INPUT);
	pinMode(IN2, INPUT);
	pinMode(IN3, INPUT);
	pullUpDnControl(IN0, PUD_OFF);
	pullUpDnControl(IN1, PUD_OFF);
	pullUpDnControl(IN2, PUD_OFF);
	pullUpDnControl(IN3, PUD_OFF);
	numlines = 0;
	DAQ_flag = false;
	return 0; // no error
}

// request one of five channels from mux, return integer value of 4-bit read 0-15
int SSBTGPIO::readADC(int chn){
	// select channel from multiplexer
	if(chn == 3){
		digitalWrite(MPLXR1,1);
		digitalWrite(MPLXR0,1);
	}else if(chn == 2){
		digitalWrite(MPLXR1,1);
		digitalWrite(MPLXR0,0);
	}else if(chn == 1){
		digitalWrite(MPLXR1,0);
		digitalWrite(MPLXR0,1);
	}else if(chn == 0){
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

int SSBTGPIO::getNumLines(){
	df_cur = datafile.tellg();
	datafile.seekg(0, ios::beg);
	df_begin = datafile.tellg();
	datafile.seekg (0, ios::end);
	df_end = datafile.tellg();
	datafile.seekg(df_begin);
	numlines = count(istreambuf_iterator<char>(datafile), istreambuf_iterator<char>(), '\n') - lines_done;
	datafile.seekg(df_cur);
	return numlines;
}

void SSBTGPIO::incLinesDone(){
	lines_done++;
}

int SSBTGPIO::readFile(){
	// how big is file now? did the DAQ hardware add more data points?
	// iterate through entire file and count lines
	df_cur = datafile.tellg();
	datafile.seekg(0, ios::beg);
	df_begin = datafile.tellg();
	datafile.seekg (0, ios::end);
	df_end = datafile.tellg();
	datafile.seekg(df_begin);
//	cout << "file length: " << df_end - df_cur << "\n";
	numlines = count(istreambuf_iterator<char>(datafile), istreambuf_iterator<char>(), '\n') - lines_done;
//	cout << "numlines: " << numlines << "\n";
	datafile.seekg(df_cur);

	// get some points from the file and put them in point1 and point2
	bool done = false;
	if (datafile){
		string s;
		if (getline( datafile, s )){
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

void SSBTGPIO::DAQisr(){
	DAQ_flag = !DAQ_flag;		// switch triggers isr despite position
	if(DAQ_flag){
		df_cur = datafile.tellg();
		datafile.seekg (0, ios::end);
		datafile << readADC(0) << ", " << readADC(1) << "\n";
		datafile.seekg(df_cur);
	}
}
