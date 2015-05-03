//intial code  11/6/2012.
//Modified 23/6/2012 to add extra fields in.  Also added in the vector function.
//The idea is that this class is of frames, and the vector function can build
//a queue of the frames.
//The queue of frames can then be scheduled for transmission.
#include <iostream>
#include <fstream>
#include <vector>
#ifndef FRAME_H
#define FRAME_H
using namespace std;
//
//
//
class Frame
{
private:
	int frameID;
	int frameSize;
	int UserID;
	int Time;
	int PD;
	int TOS;
public:
	void frameInit(Frame frame);
	vector<Frame> enqueueFrame(FILE *InputFile);
	void getFrameInfo(Frame &frame);
	vector<Frame> GetFrameForTX(int i, vector<Frame> &currentQueue);
	bool getFrameToTX(int i, Frame &frame);
};
#endif
//
//
