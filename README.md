check the pull requests for the most recent code!! the main branch contains what is stable.

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
sudo apt install liballegro5
sudo apt install liballegro5-dev

CSOUND:
https://csound.com/download.html
sudo apt install csound
sudo apt install libcsnd-dev
