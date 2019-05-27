# sonified-space-browsing-tool
A *prototype* that creates sound-emitting objects in a 5.1 surround space and allows a user to explore the space. Experiment with the effectiveness of mapping datasets to amplitude and panning parameters. _This project needs work to run on your machine. See "Some Help Getting This To Run"._

**SYSTEM RECOMMENDATIONS:**
* Raspbian Stretch (Linux Kernal 4.14)
* Allegro 5.2
* Csound 6.12.0
* DiamondAudio 7.1 USB Sound Card (don't use SS-OUT channel)
* A DAQ circuit: 4-bit ADC, 2-channel analog MUX, a switch

**OPERATING SYSTEMS:**
* Raspbian Stretch tests succeeded.
* Ubuntu Xerial Xerus tests failed, due to dependency Allegro 5.2 not supported by OS
* Microsoft Windows and MacOS not tested.

**DEPENDENCIES:**

ALLEGRO: \
https://liballeg.org/download.html \
`sudo apt install liballegro5` \
`sudo apt install liballegro5-dev` 

CSOUND: \
https://csound.com/download.html \
`sudo apt install csound`\
`sudo apt install libcsnd-dev` 

WIRINGPI: \
http://wiringpi.com/download-and-install/ \
`(pre-installed on Raspbian)`

COMPILE: \
`g++ main.cpp application.cpp application.h rabbit.h rabbit.cpp user.h user.cpp ssbtsound.cpp ssbtsound.h ssbtgpio.cpp ssbtgpio.h constants.h pkg-config --libs allegro-5 allegro_primitives-5 -lcsound64 -lwiringPi`

**SOME HELP GETTING THIS TO RUN**
It is likely that this code will take your entire day or longer to get up and running. The development team will not share the copyrighted audio files used in development. Read everything here before you try anything.

AUDIO: You will need to cut some audio to 64 beats of 145 bpm (aka 16 measures 4/4 time) in mono. I recommend audacity and cambridge multitrack audio library. You will need four instruments and two songs (chorus and verse is fine). Enter in times from the keyboard and cut precisely. Modify the Csound program's F table to the proper filenames. Keep files in the working directory. It is recommended to use a metronome or any strict quarter note drum pattern for the drum acknowledge audio. 

INSTALLATION: Get all of the dependencies listed above. If you donot have a touch screen and/or 5.1 surround sound system, you will quite literally have to finish the code for us. Apologies. Look for anything pertaining to MODE_FLAGS. The compatability code is currently there but incomplete. You may have better luck taking the sound server out and programming the game yourself. There is a stereo Csound program available in pull request 15. Use it and ssbtsound.cpp and ssbtsound.h.

CSV DATABASES: Two numbers per line separated by a comma. No comma at the end of lines. Numbers must be within range [0,15] inclusive. End the file on a new line. Use pull request 25 (the demonstration code). You will have one sound emitting object and one sound listening object. Pull request 25 does work with DAQ circuits, but they will not be sonified in real-time. You may prefer it that way depending on your application.

DAQ CIRCUITS: Use pull request 21 (video1). You will have four sound emitting objects and one sound listening object. The sound emitting objects will refresh in real-time. The "got the fox" earcon is present in all commits pull request 21 and after. <a href="https://trello-attachments.s3.amazonaws.com/5bb5860efb637c0ff845d12f/5ca38ff5678c046f6a84b3f7/ecdb25d5f8ca845ec71be37b53a4b396/schem.jpg">The circuit goes a little something like this.</a>
