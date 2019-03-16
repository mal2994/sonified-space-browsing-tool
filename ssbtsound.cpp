#include <csound/csound.hpp>
#include <csound/csPerfThread.hpp>
#include <iostream>
#include <stdio.h>									// for sprintf()
#include <stdlib.h>
#include "ssbtsound.h"

using namespace std;

Ssbtsound::Ssbtsound(){
	// cpp csound variables. will be sent via software bus elsewhere. dont need them at csound start.
	cswaitstate = false;
	for(int i = 0; i < NUMRABBITS; i++) distance_chns[i] = 0.0;
	for(int i = 0; i < NUMRABBITS; i++) angle_chns[i] = 0.0;
	drumackamp = 0.0;
	csound = new Csound();														// create an instance of Csound
	csound->Compile("genrrm2.csd");										// compile instance of csound
	CsoundPerformanceThread* perfThread = new CsoundPerformanceThread(csound); // setup performance thread
	perfThread->Play();																// start Csound performance
}

Ssbtsound::~Ssbtsound(){
	perfThread->Stop();
	delete perfThread;
	delete csound;
};
// MODIFICATION MEMBER FUNCTIONS //
void Ssbtsound::setCsWaitState(bool a){
	cswaitstate = a;
}
void Ssbtsound::setDistanceChn(int i, float a){
	char buffer[10];	// todo would 11 be ok so we can do more than 9 rabbits?
	int error = 0;
	distance_chns[i] = a;
	error = sprintf(buffer, "r%ddistance", i);
	if(error > 0){																	// no error then
		csound->SetChannel(buffer, distance_chns[i]);	// pass complement of distance as float to csound for amplitude adjustment
	}else{
		cout << "Error: sprintf failed for distance.\n";
	}
	cout << "Rabbit " << i << " distance channel = " << distance_chns[i] << "\n";
}
void Ssbtsound::setAngleChn(int i, float a){
	char buffer[7];		// todo would 8 be ok so we can do more than 9 rabbits?
	int error = 0;
	angle_chns[i] = a;
	error = sprintf(buffer, "r%dangle", i);
	if(error > 0){
		csound->SetChannel(buffer, angle_chns[i]);
	}else{
		cout << "Error: sprintf failed for angle.\n";
	}
	cout << "Rabbit " << i << " angle channel = " << angle_chns[i] << "\n";
}
void Ssbtsound::setDrumAckAmp(float a){
	drumackamp = a;
}
// CONSTANT MEMBER FUNCTIONS //
bool Ssbtsound::getCsWaitState(){
	return cswaitstate;
}
float Ssbtsound::getDistanceChn(int i){
	return distance_chns[i];
}
float Ssbtsound::getAngleChn(int i){
	return angle_chns[i];
}
float Ssbtsound::getDrumAckAmp(){
	return drumackamp;
}
