#pragma once // todo when ifndef in ssbtsound.h AND every file that includes it STILL doesnt do the trick, pragma once.
#ifndef SSBTSOUND_H
#define SBBTSOUND_H
#include <csound/csound.hpp>				/* TODO remove csound headers and see if it compiles */
#include <csound/csPerfThread.hpp>
#include "rabbit.h"									// for NUMRABBITS

class Ssbtsound
{
	public:
		Ssbtsound();
		~Ssbtsound();
		// MODIFICATION MEMBER FUNCTIONS //
//		void createAndCompile(void);		MOVED: this is in constructor
//		void endAndDestroyCsound(void); MOVED: this is in destructor
		void setCsWaitState(bool);
		void setDistanceChn(int, float);
		void setAngleChn(int, float);
		void setDrumAckAmp(float);	// usually 0.0 or 1.0
		// CONSTANT MEMBER FUNCTIONS //
		bool getCsWaitState(void);
		float getDistanceChn(int);
		float getAngleChn(int);
		float getDrumAckAmp(void);

	private:
		Csound* csound;
		CsoundPerformanceThread* perfThread;
		bool cswaitstate;
		float distance_chns[NUMRABBITS];
		float angle_chns[NUMRABBITS];
		float drumackamp;
};

#endif
