#pragma once // todo when ifndef in ssbtsound.h AND every file that includes it STILL doesnt do the trick, pragma once.
#ifndef SSBTSOUND_H
#define SBBTSOUND_H
#include <csound/csound.hpp>
#include <csound/csPerfThread.hpp>
#include "rabbit.h"									// for NUMRABBITS

#define NUMSONGS 2									// remember that in csound the songs are 0-based numbering (so put a -1 on NUMSONGS)

class Ssbtsound
{
	public:
		Ssbtsound();
		~Ssbtsound();
		// MODIFICATION MEMBER FUNCTIONS //
		void setCsWaitState(bool);
		void setDistanceChn(int, float);
		void setAngleChn(int, float);
		void setDrumAckAmp(float);	// usually 0.0 or 1.0
		void flipChannels(bool);
		// CONSTANT MEMBER FUNCTIONS //
		void compileCsound(bool*);
		int startPerformanceThread();
		bool getCsWaitState(void);
		float getDistanceChn(int);
		float getAngleChn(int);
		float getDrumAckAmp(void);
		void setSwishAmp(float);
		Csound* csound;

	private:
		CsoundPerformanceThread* perfThread;
		bool cswaitstate;
		float distance_chns[NUMRABBITS];						// software buses to Csound 
		float angle_chns[NUMRABBITS];								// software buses to Csound 
		float drumackamp;
		float swishamp;
		int song;
		bool firstcall;
};

#endif
