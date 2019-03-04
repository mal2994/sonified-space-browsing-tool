/*	there are advantages to recompilation.
	there is no metronome drift, provided the compilation and trigger occur correctly
	its easier to prototype
	BUT this could be implemented entirely in MIDI and krate instructions
	at least I think it could. diskin2 can read from the score
	and the score parameter can be read from MIDI
*/

#ifndef SSBTSOUND_H
#define SBBTSOUND_H
#include <csound/csound.h>

class Ssbtsound
{
	public:
		Ssbtsound();
		~Ssbtsound();
		void DestroySsbtsound(void);
		void compileAndPlay(float);
	private:
		char *csd_text1;
		char *csd_text2;
		char *csd_textf;
		CSOUND *csound;
};

#endif
