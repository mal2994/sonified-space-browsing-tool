# sonified-space-browsing-tool
in progress code that creates sound-emitting objects in a 5.1 surround space and allows a user to explore the space.
one day, maybe an API.

SSBT Release Notes March 22, 2019
Applicable to PATCH 16 and after

OVERVIEW:
Ssbt will start, play sounds in 5.1, and identify gestures. If it does not, that is a problem dependent on your system.
Wedge/disc isolation needs work. Teleport needs work. User io modes need work.
In an attempt to aid the development process, user io modes were introduced before user functions were completed.


SYSTEM REQUIREMENTS:
Raspbian Stretch (Linux Kernal 4.14), Debian Stretch should be fine.
Allegro 5.2
Csound 6.12.0

OPERATING SYSTEMS:
Raspbian Stretch tests succeeded.
Ubuntu Xerial Xerus tests failed, due to dependency Allegro 5.2 not supported by OS

ALLEGRO:
https://liballeg.org/download.html
sudo apt install liballegro5.2

CSOUND:
https://csound.com/download.html
sudo apt install csound
sudo apt install libcsnd-dev


NEEDS WORK:
wedge/disc isolation: Problem is unknown (update mar 24: the isolation code is never called.)

teleport: Problems with calculating azimuth have been corrected, but possibly could be better compartmentalized. Problems with vbaplsinit have been corrected (dummy channels). Distance attenuation needs tweaked to a model comfortable to user. Testing must be done to determine more problems!

user iomodes: Keyboard events imitating touch screen events need fixed. Read-from-file/Read-from-sensor modes have not begun. Autodetect screen size would be nice. Testing must be done to determine more problems!

makefile: either do the makefile or get the shell script uploaded

ADDITIONS SINCE PATCH 15
Multiple rabbits supported in csound. SSBTSOUND_H has been refactored in its entireity. Main loop restructured with drum acknowledge. #define for different size screens.
