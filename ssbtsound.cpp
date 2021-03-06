#include <csound/csound.hpp>
#include <csound/csPerfThread.hpp>
#include <iostream>
#include <stdio.h>	// for sprintf()
#include <stdlib.h>
#include "ssbtsound.h"
#include "application.h"
#include "constants.h"
using namespace std;

Ssbtsound::Ssbtsound(){
	cswaitstate = false;
	for(int i = 0; i < NUMRABBITS; i++) distance_chns[i] = 0.0;
	for(int i = 0; i < NUMRABBITS; i++) angle_chns[i] = 0.0;
	drumackamp = 0.0;
	swishamp = 0.0;
	csound = new Csound();														// create an instance of Csound
	perfThread = new CsoundPerformanceThread(csound); // setup performance thread
	song = 0;
	firstcall = true;
}

Ssbtsound::~Ssbtsound(){
	perfThread->Stop();
	delete perfThread;
	delete csound;
};

void Ssbtsound::compileCsound(bool* mode_flags){
	if(mode_flags[STEREO_FLAG]){
		if(mode_flags[HRTF_FLAG]){
			csound->Compile("ssbt2hrtf.csd");
		}else{
			csound->Compile("ssbt2.csd");
		}
	}else if (mode_flags[SUR51_FLAG]){
			csound->Compile("ssbt51.csd");
	}else if (mode_flags[SUR71_FLAG]){
			csound->Compile("ssbt71.csd");
	}
}

// MODIFICATION MEMBER FUNCTIONS //
void Ssbtsound::setCsWaitState(bool a){
	cswaitstate = a;
}

void Ssbtsound::setDistanceChn(int i, float a){
	distance_chns[i] = a;
}

void Ssbtsound::setAngleChn(int i, float a){
	angle_chns[i] = a;
}

void Ssbtsound::setDrumAckAmp(float a){
	drumackamp = a;
	csound->SetChannel("drumackamp", drumackamp);		// this channel flips independent of others 
}

void Ssbtsound::setSwishAmp(float a){
	swishamp = a;
}

void Ssbtsound::playAll(){
	for(int i=0;i<NUMINSTR;i++){
		distance_chns[i] = 0.75;
		angle_chns[i] = 0;
	}
	flipChannels(false);
}

// similar to allegro_flip_display...set em at different times then flip em all at once
void Ssbtsound::flipChannels(bool newsong){
//to pass a channel name as string to csound
	char bufferD[10];
	char bufferA[7];

	for(int i = 0; i < NUMINSTR; i++){
		sprintf(bufferD, "r%ddistance", i);
		csound->SetChannel(bufferD, distance_chns[i]);		// example: chnset 20, "r0distance"
		cout << "Rabbit " << i << " distance channel = " << distance_chns[i] << "\n";

		sprintf(bufferA, "r%dangle", i);
		csound->SetChannel(bufferA, angle_chns[i]);			// example: chnset 180, "r0angle"
		cout << "Rabbit " << i << " angle channel = " << angle_chns[i] << "\n";
	}

	csound->SetChannel("swishamp",swishamp);					// "you've got the fox" earcon

	if(newsong){
			song = (song+1)%NUMSONGS;
			csound->SetChannel("song",(float)song);
	}
}

// CONSTANT MEMBER FUNCTIONS //
int Ssbtsound::startPerformanceThread(){
	perfThread->Play();
	return 0;
}
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
