# sonified-space-browsing-tool
A prototype that creates sound-emitting objects in a 5.1 surround space and allows a user to explore the space. Experiment with the effectiveness of mapping datasets to amplitude and panning parameters. _This code may need work to run on your machine._

SYSTEM RECOMMENDATIONS:
* Raspbian Stretch (Linux Kernal 4.14)
* Allegro 5.2
* Csound 6.12.0
* DiamondAudio 7.1 USB Sound Card (don't use SS-OUT channel)
* A DAQ circuit: 4-bit ADC, 2-channel analog MUX, a switch

OPERATING SYSTEMS:
* Raspbian Stretch tests succeeded.
* Ubuntu Xerial Xerus tests failed, due to dependency Allegro 5.2 not supported by OS
* Microsoft Windows and MacOS not tested.

ALLEGRO:
https://liballeg.org/download.html \
`sudo apt install liballegro5 \
sudo apt install liballegro5-dev` \

CSOUND:
https://csound.com/download.html \
`sudo apt install csound \
sudo apt install libcsnd-dev` \

WIRINGPI:
http://wiringpi.com/download-and-install/ \
`(pre-installed on Raspbian)`
