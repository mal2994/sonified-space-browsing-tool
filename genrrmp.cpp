//#include "csound.h"
#include <csound/csound.h>
//#include <csound/csound.hpp>
#include <stdlib.h>
#include <fstream>
using namespace std;

int main(int argc, char **argv)
{
 ofstream myfile;
 myfile.open ("genrrmp.csd");
 char *csd_text1 =
 "<CsoundSynthesizer>\n"
 "<CsOptions>\n"
 "; Select audio/midi flags here according to platform\n"
 " -odac     ;;;realtime audio out\n"
 ";-iadc    ;;;uncomment -iadc if real audio input is needed too\n"
 "; For Non-realtime ouput leave only the line below:\n"
 "; -o genrrmp.wav -W ;;; for file output any platform\n"
 "</CsOptions>\n"
 "<CsInstruments>\n\n"

 "sr = 44100\n"
 "ksmps = 32\n"
 "nchnls = 2\n"
 "0dbfs  = 1\n\n"

 "giSine ftgen 0, 0, 2^10, 10, 1\n\n"

 "instr 1\n\n"

 "kazim = ";
 
 float kazim = 22.5;
 
 char *csd_text2 =
 "\n"
 "ain     oscili  .6, 440, giSine ; audio signal..\n"
// "aL,aR   pan2    ain, kline   ; sent across image\n"
  "aL,aR   pan2    ain, kazim   ; sent across image\n"
 "        outs    aL, aR\n\n"

 "endin\n"
 "</CsInstruments>\n"
 "<CsScore>\n"
 "i1 0 5\n"
 "e\n"
 "</CsScore>\n"
 "</CsoundSynthesizer>\n";
	char *csd_textf = (char*)malloc( sizeof(char) * ( 2000 ) );
	int result;
//	CSOUND *csound;//void *csound;
	//while(1){		
//	  	csound = csoundCreate(0);								
//	  	result = csoundCompileCsdText(csound,  csd_textf);	
		
	printf("kazim? \n");
	scanf("%f",&kazim);
	csound = csoundCreate(0);								
	sprintf(csd_textf,"%s%f%s",csd_text1,kazim,csd_text2);				
	result = csoundCompileCsdText(csound,  csd_textf);
	myfile << csd_textf;
	myfile.close();
	//sleep(1);
	result = csoundStart(csound);
	while (1) {
	  result = csoundPerformKsmps(csound);
	  if (result != 0) {
		  break;
	  }
	}
    	result = csoundCleanup(csound);
  	  	csoundReset(csound);
	  	//if(execlp("aplay genrrmp.wav",NULL) == -1)	perror("[P] could not execlp");	   	// execute another C program (ie ./child2) in a process. with error checking.
	  	//if(system("csound genrrmp.csd") == -1)	perror("[P] could not system call");	   	// execute another C program (ie ./child2) in a process. with error checking.

  //}
//  csoundDestroy(csound);
  return result;
}
