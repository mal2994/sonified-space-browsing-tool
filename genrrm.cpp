//testing genrrm.csd as a unit isolated from ssbt

#include <stdio.h>
#include <csound/csound.hpp>
#include <csound/csPerfThread.hpp>
#include <iostream>

using namespace std;

int main()
{
	float knob = 1;
	bool shouldPlay = true;
	
	//Create an instance of Csound
	Csound* csound = new Csound();

	//compile instance of csound.
	csound->Compile("genrrm2.csd");
	//csound->SetChannel("chnget1", knob);
	//setup performance thread
	CsoundPerformanceThread* perfThread = new CsoundPerformanceThread(csound); 

	//start Csound performance
	perfThread->Play();

	//keep the application running while performance is ongoing and checks for incoming frequencies 
	//from the user 
	while(perfThread->GetStatus() == 0 && shouldPlay)
	{
		cout << " \"probably not a frequency but a kazim or something [its kpitch rn]\"-rrm\n";
		cout << "Enter a frequency and press enter(enter a negative frequency to quit):";
		cin >> knob;
		if(knob>=0)
			csound->SetChannel("chnget2", knob); 
		else
		{
			cout << "Stopping Csound";
			perfThread->Stop();
			shouldPlay = false;
		}
	}
	//free thread object
	delete perfThread;
	//free Csound object
	delete csound;
	return 0;
}
