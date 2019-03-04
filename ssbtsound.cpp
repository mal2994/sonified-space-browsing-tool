#include <csound/csound.h>
#include <iostream>
#include <stdlib.h>
#include "ssbtsound.h"

using namespace std;

Ssbtsound::Ssbtsound()
{
	char *csd_text1 =  
		"<CsoundSynthesizer>\n"
		 "<CsOptions>\n"
		 "; Select audio/midi flags here according to platform\n"
		 "-odac     ;;;realtime audio out\n"
		 ";-iadc    ;;;uncomment -iadc if real audio input is needed too\n"
		 "; For Non-realtime ouput leave only the line below:\n"
		 "; -o pan2.wav -W ;;; for file output any platform\n"
		 "</CsOptions>\n"
		 "<CsInstruments>\n\n"
		 "sr = 44100\n"
		 "ksmps = 32\n"
		 "nchnls = 2\n"
		 "0dbfs  = 1\n\n"
		 "giSine ftgen 0, 0, 2^10, 10, 1\n\n"
		 "instr 1\n\n"
		 "kazim = ";
	char *csd_text2 =  "\n"
		"ain     oscili  .6, 440, giSine ; audio signal..\n"
		 "aL,aR   pan2    ain, kazim   ; sent across image\n"
		"        outs    aL, aR\n\n"
		"endin\n"
		"</CsInstruments>\n"
		"<CsScore>\n"
		"i1 0 5\n"
		"e\n"
		"</CsScore>\n"
		"</CsoundSynthesizer>\n";
	char *csd_textf = (char*)malloc(sizeof(char)*(2000));
	CSOUND *csound;
}

void Ssbtsound::DestroySsbtsound()
{
	csoundCleanup(csound);
	csoundReset(csound);
	csoundDestroy(csound);
}

Ssbtsound::~Ssbtsound(){};

void Ssbtsound::compileAndPlay(float kazim)
{
	int result;
	printf("entered: %f\n",kazim);
	sprintf(csd_textf,"%s%f%s",csd_text1,kazim,csd_text2);

	csound = csoundCreate(0);
	result = csoundCompileCsdText(csound,csd_textf);
	result = csoundStart(csound);
	while (1) {
		result = csoundPerformKsmps(csound);
		if (result != 0) {
			break;
		}
	}
}
