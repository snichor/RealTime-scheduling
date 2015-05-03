//intial code  11/07/2012.
//This is where the packet scheduling takes place.
//There is some work to do on this class.
//But basically, the scheduler will mainly be functions, which can then use the
//class values and manipulate them, so to speak.
//Suspect this function needs to go in a transmit.h file.
//
#include <iostream>
#include <fstream>
#include <vector>
#include "user.h"
#include "frame.h"
#ifndef ChannelQuality_H
#define ChannelQuality_H
using namespace std;
//
//
//
class ChannelQuality
{
private:
//
//So have vector<Frame> candidateFrames
//
//And this vector will change in size, depending on whether
//the frames have been transmitted, or reached maximum transmission count.
//One issue: Does the frame type need adjusting to account to transmissions?
//
	//int UserID;
	//int Time;
	//int CQI;
	float LowerLimit;
	float UpperLimit;
	int DataRate;
public:
	
//Probably have a small vectore of frames here t transmit.
//So have some functions that are each a small vector of frames.
//Each function will be a specific packet scheduler.
//
	//
 	vector<ChannelQuality> ReadInLimits(FILE *LimitFile);
	//int findCQI(float);
	float FindRate(float, vector<ChannelQuality>);
	int FindCQI(float, vector<ChannelQuality>);
	//vector<ResourceBlock> GetRBsForTX(int i, vector<ResourceBlock> &RB);
};
#endif
//
//
