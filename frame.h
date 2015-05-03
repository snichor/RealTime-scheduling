//intial code  11/6/2012.
//Modified 23/6/2012 to add extra fields in.  Also added in the vector function.
//The idea is that this class is of frames, and the vector function can build
//a queue of the frames.
//The queue of frames can then be scheduled for transmission.
#include <iostream>
#include <fstream>
#include <vector>
#include "user.h"
#ifndef FRAME_H
#define FRAME_H
using namespace std;
//
//
//class UserEquipment;
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
	int TXattempt;
	bool ACK;
	int Delay;
public:
	void frameInit(Frame frame);
	vector<Frame> enqueueFrame(FILE *InputFile, int NumUsers);
	void getFrameInfo(Frame &frame);
	vector<Frame> GetFrameForTX(int i, vector<Frame> &currentQueue);
	bool getFrameToTX(int i, Frame &frame);
	Frame ChangeStatusToTransmitted(Frame &frame);
	Frame ChangeStatusToDropped(Frame &frame);
	Frame SetFrameACKtoTrue(Frame &frame);
	//Frame SetFrameDelay(Frame &frame);
	bool checkFrameTXattempt(Frame &frame);
	bool checkFrameMaxTX(Frame &frame);
	bool checkFramePLR(Frame &frame);
	int GetTXattempt(Frame &frame);
	int CheckStatusTX(Frame &frame);	
	int CheckUserID(Frame &frame);	
	int CheckFrameID(Frame &frame);	
	int GetFrameSize(Frame &frame);
	int CheckDelay(Frame &frame); 
	Frame SetDelay(Frame &frame, int FrameDelay); 
	bool CheckACK(Frame &frame);
	int AssignRand(Frame &frame);
	int GetDelay(Frame &frame); 
	int GetTOS(Frame &frame); 
};
#endif
//
//
