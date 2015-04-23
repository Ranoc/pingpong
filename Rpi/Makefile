# The recommended compiler flags for the Raspberry Pi
CCFLAGS=-Ofast -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s

all: pingpong.o
        g++ pingpong.o -o pingpong -lrf24-bcm

pingpong.o: pingpong.cpp pingpong.h
        g++ -Wall -I../ ${CCFLAGS} -c pingpong.cpp


