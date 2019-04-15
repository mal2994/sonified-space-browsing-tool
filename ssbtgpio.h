#ifndef SSBTGPIO_H_
#define SSBTGPIO_H_

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
using namespace std;

#define IN0			0	// header pin 11 lsb
#define IN1			1 // header pin 12
#define IN2			2 // header pin 13
#define IN3			3 // header pin 15
#define MPLXR0	4 // header pin 16
#define MPLXR1	5 // header pin 18
#define MPLXR2	6 // header pin 22

class SSBTGPIO {
public:
	SSBTGPIO();
	~SSBTGPIO();
	int setUpPins(void);
	int readChn(int);					// return integer value of 4-bit read
	int readFile();
	int getPoint1(void);
	int getPoint2(void);
private:
	int pins[7] = {0,0,0,0,0,0,0};
	int point1, point2;
	ifstream infile;
};

#endif
