# this is sort of a replacement for a makefile...installs the packages you need
# it is recommended to build from source, but if you wanna apt install it, go ahead
# to build from source, visit allegro wiki

echo -n "sudo apt install build-essential git cmake cmake-curses-gui xorg-dev libgl1-mesa-dev libglu-dev"
read cont
sudo apt install build-essential git cmake cmake-curses-gui xorg-dev libgl1-mesa-dev libglu-dev
# ~67 MB on a new system

echo -n "sudo apt install liballegro5-dev"
read cont
sudo apt install liballegro5-dev
# ~134 MB on a new system
# btw this should install liballegro5.0 (typo?) for you, but if it doesnt, please go do that... (reading this later i have no idea what that means)

# not sure which are really needed (REMOVED. We are no longer using OpenAL and Allegro Sound!)
#echo -n "sudo apt install libasound-dev libpulse-dev libdumb1-dev libopenal-dev"
#read cont
#sudo apt install libasound-dev libpulse-dev libdumb1-dev libopenal-dev

echo -n "sudo apt install libcsnd-dev"
read cont
sudo apt install libcsnd-dev

echo -n "sudo apt install liballegro5.2"
read cont
sudo apt install allegro5.2

echo -n "sudo apt install csound"
read cont
sudo apt install csound

# NOTES ON INSTALLING #

#pkg-config --libs --cflags allegro-5.0
# -I/usr/include/x86_64-linux-gnu THIS SHOULD WORK ON AMD ANYWAY
# PROVED WORKING:
#pi@raspberrypi:~ $ pkg-config --libs --cflags allegro-5
#-I/usr/include/arm-linux-gnueabihf -lallegro

# INSTALLING MORE THAN ONE ALLEGRO WILL CONFLICT #
# from apt show liballegro5-dev
#Conflicts: liballegro-dev, liballegro4-dev
#sudo apt show liballegro*
# there is liballegro4-dev liballegro5-dev liballegro-dev liballegro5.0 liballegro-dev-common liballegro4a liballegro4.4
# make sure you have the right one (when messing with packages sudo apt autoremove is your friend)
# PROVED WORKING:
# sudo apt list --installed | grep allegro
#pi@raspberrypi:~/Documents/sonified-space-browsing-tool $ sudo apt list --installed | grep allegro
#allegro5-doc/stable,now 2:5.2.2-1 all [installed]
#liballegro-acodec5.2/stable,now 2:5.2.2-1 armhf [installed,auto-removable]
#liballegro-audio5.2/stable,now 2:5.2.2-1 armhf [installed,auto-removable]
#liballegro-dialog5-dev/stable,now 2:5.2.2-1 armhf [installed,automatic]
#liballegro-dialog5.2/stable,now 2:5.2.2-1 armhf [installed,automatic]
#liballegro-image5-dev/stable,now 2:5.2.2-1 armhf [installed,automatic]
#liballegro-image5.2/stable,now 2:5.2.2-1 armhf [installed,automatic]
#liballegro-physfs5-dev/stable,now 2:5.2.2-1 armhf [installed,automatic]
#liballegro-physfs5.2/stable,now 2:5.2.2-1 armhf [installed,automatic]
#liballegro-ttf5-dev/stable,now 2:5.2.2-1 armhf [installed,automatic]
#liballegro-ttf5.2/stable,now 2:5.2.2-1 armhf [installed,automatic]
#liballegro-video5.2/stable,now 2:5.2.2-1 armhf [installed,auto-removable]
#liballegro5-dev/stable,now 2:5.2.2-1 armhf [installed]
#liballegro5.2/stable,now 2:5.2.2-1 armhf [installed,automatic]

# I have come to the conclusion that ssbt will not compile on Ubuntu 16.04 (which is what I have), need to update to 18
