CC=g++
CFLAGS=-c -Wall

all: coremodule

coremodule: user.o frame.o core.o PacketScheduler.o ChannelQuality.o CLI.o eNodeB.o
	$(CC) user.o frame.o core.o PacketScheduler.o ChannelQuality.o  CLI.o -o coremodule

user.o: user.cpp
	$(CC) $(CFLAGS) user.cpp

frame.o: frame.cpp
	$(CC) $(CFLAGS) frame.cpp

PacketScheduler.o: PacketScheduler.cpp
	$(CC) $(CFLAGS) PacketScheduler.cpp

ChannelQuality.o: ChannelQuality.cpp
	$(CC) $(CFLAGS) ChannelQuality.cpp

CLI.o: CLI.cpp
	$(CC) $(CFLAGS) CLI.cpp

core.o: core.cpp
	$(CC) $(CFLAGS) core.cpp

eNodeB.o: eNodeB.cpp
	$(CC) $(CFLAGS) eNodeB.cpp

clean:
	rm -rf *o coremodule 
install:
	cp -p coremodule ../test/bin
