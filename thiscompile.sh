read -p "reason for compiling: " myvar
date >> ./compilehistory.txt
echo -ne " $myvar \n" >> ./compilehistory.txt
echo "compiling..."
# on raspberry pi 
g++ main.cpp application.cpp application.h rabbit.h rabbit.cpp user.h user.cpp ssbtsound.cpp ssbtsound.h ssbtgpio.cpp ssbtgpio.h `pkg-config --libs allegro-5 allegro_primitives-5` -lcsound64 -lpthread -lcsnd6 -lwiringPi -ocsPerfThreadExample -o ssbt --std=c++11
#g++ angledistance.cpp application.cpp application.h rabbit.h rabbit.cpp user.h user.cpp ssbtsound.cpp ssbtsound.h `pkg-config --libs allegro-5 allegro_primitives-5` -lcsound64 -lpthread -lcsnd6 -ocsPerfThreadExample -o ssbt --std=c++11

#g++ main.cpp application.cpp application.h rabbit.h rabbit.cpp user.h user.cpp ssbtsound.cpp ssbtsound.h `pkg-config --libs allegro-5.0 allegro_primitives-5.0 allegro_image-5.0` -lcsound64 -lpthread -lcsnd6 -ocsPerfThreadExample -o ssbt --std=c++11
#g++ main.cpp application.cpp application.h rabbit.h rabbit.cpp user.h user.cpp ssbtsound.cpp ssbtsound.h `pkg-config --cflags --libs allegro-5.0 allegro_acodec-5.0 allegro_audio-5.0 allegro_color-5.0 allegro_dialog-5.0 allegro_font-5.0 allegro_image-5.0 allegro_main-5.0 allegro_memfile-5.0 allegro_physfs-5.0 allegro_primitives-5.0 allegro_ttf-5.0` -lcsound64 -lpthread -lcsnd6 -ocsPerfThreadExample -o ssbt #--std=c++11
# hey i know we were working on a makefile. i also put the link on the trello for this:
#CXX=g++
#CFLAGS=
#LDFLAGS=-L/usr/lib -lallegro
#INCLUDE=-I. -I/usr/include/allegro5
#
#OBJS=hello.o
#OUT=hello
#
#all: hello_rule
#
#clean:
#        rm -rf *.o hello
#
#hello_rule: $(OBJS)
#        $(CXX) $(OBJS) -o $(OUT) $(INCLUDE) $(CFLAGS) $(LDFLAGS)
#https://stackoverflow.com/questions/6560760/how-do-i-link-allegro-5-from-my-makefile
