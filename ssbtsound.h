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
		void setCsWaitState(bool);
		void setDistanceChn(int, float);
		void setAngleChn(int, float);
		///void newWavs(...)
		void setDrumAckAmp(float);	// usually 0.0 or 1.0
		void flipChannels(void);
		// CONSTANT MEMBER FUNCTIONS //
		void compileCsound(bool*);
		int startPerformanceThread();
		bool getCsWaitState(void);
		float getDistanceChn(int);
		float getAngleChn(int);
		float getDrumAckAmp(void);

		Csound* csound;

	private:
		//Csound* csound;		//todo make private
		CsoundPerformanceThread* perfThread;
		bool cswaitstate;
		float distance_chns[NUMRABBITS];						// they might be called software buses, but the Csound API says SetChannel() so...
		float angle_chns[NUMRABBITS];
		float drumackamp;
};

#endif
