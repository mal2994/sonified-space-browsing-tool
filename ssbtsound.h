#pragma once
#ifndef SSBTSOUND_H
#define SBBTSOUND_H
#include <csound/csound.hpp>
#include <csound/csPerfThread.hpp>
#include "rabbit.h"
#include "constants.h"

class Ssbtsound
{
	public:
		Ssbtsound();
		~Ssbtsound();
		// MODIFICATION MEMBER FUNCTIONS //
		void setCsWaitState(bool);
		void setDistanceChn(int, float);
		void setAngleChn(int, float);
		void setDrumAckAmp(float);
		void flipChannels(bool);
		// CONSTANT MEMBER FUNCTIONS //
		void compileCsound(bool*);
		int startPerformanceThread();
		bool getCsWaitState(void);
		float getDistanceChn(int);
		float getAngleChn(int);
		float getDrumAckAmp(void);
		void setSwishAmp(float);
		void playAll();
		Csound* csound;

	private:
		CsoundPerformanceThread* perfThread;
		bool cswaitstate;
		float distance_chns[NUMINSTR];	// software buses to Csound
		float angle_chns[NUMINSTR];			// software buses to Csound
		float drumackamp;
		float swishamp;
		int song;
		bool firstcall;
};

#endif
