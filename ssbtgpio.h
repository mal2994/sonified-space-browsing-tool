#ifndef SSBTGPIO_H_
#define SSBTGPIO_H_

#define IN0			0	// header pin 11
#define IN1			1 // header pin 12
#define IN2			2 // header pin 13
#define IN3			3 // header pin 15
#define MPLXR0	4 // header pin 16
#define MPLXR1	5 // header pin 18

class SSBTGPIO {
public:
	SSBTGPIO();
	~SSBTGPIO();
	int setUpPins(void);
	int readChn(int);					// return integer value of 4-bit read
private:
	int pins[6] = {0,0,0,0,0,0};
};

#endif