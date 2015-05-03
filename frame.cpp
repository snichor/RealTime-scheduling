// Inital coding  11/6/2012.
// Modified 23/6/2012.
// Modified enqueueFrame function to take a file as an argument.
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "frame.h"
#include "user.h"
using namespace std;
//
//
//
void Frame::frameInit(Frame frame)
{
	frame.Time=0;
	frame.PD=0;
	frame.frameID=0;
	frame.frameSize=0;
	frame.UserID=0;
	frame.TOS=0;
}

vector<Frame> Frame::enqueueFrame(FILE *InputFile, int NumUsers)
{
Frame frame; 
vector<Frame> PS;
int time = 0, user = 0, pd = 0, pid = 0, psize = 0, stype = 0;
int count = 0;
int RTTraffic = 0, NRTTraffic = 0;
	while (!feof(InputFile) && (count < NumUsers)) 
	{
		fscanf(InputFile,"%d",&time);
		fscanf(InputFile,"%d",&user);
		fscanf(InputFile,"%d",&pd);
		fscanf(InputFile,"%d",&pid);
		fscanf(InputFile,"%d",&psize);
		fscanf(InputFile,"%d",&stype);
		frame.Time = time;
		frame.PD = pd;
 		frame.frameID = pid;
 		frame.frameSize = psize;
 		frame.UserID = user;
		//Below is a hack to change the breakdown of frames.  Need to refine this a little more.
		if (pid % 2 == 0)
		{
			frame.TOS = 0;
			RTTraffic++;
		} else 
		{
			frame.TOS = 1;
			NRTTraffic++;
		}
		//frame.TOS = stype;
		frame.TXattempt = 0;
		frame.ACK = false;
		frame.Delay = 0;
	 PS.push_back(frame);
	count = frame.UserID;
 	}	
	cout<<"Real Time traffic = "<<RTTraffic<<endl;
	cout<<"Non Real Time traffic = "<<NRTTraffic<<endl;
return PS;

}

void Frame::getFrameInfo(Frame &frame)
{

	cout<<"Time = "<<frame.Time<<" Packet Descriptor = "<<frame.PD<<" Frame ID = "<<frame.frameID<<" User ID = "<<frame.UserID<<" TX attempt = "<<frame.TXattempt<<" ACK received = "<<frame.ACK<<endl;
}


vector<Frame> Frame::GetFrameForTX(int i, vector<Frame> &currentQueue)
//Change this to FillBuffer or something like that.
{
//Change what is passed to a frame, from a vector
int j=0;
vector<Frame> txqueue;
Frame temp;
			//cout<<"i in function = "<<i<<endl;
                      for (j=0; j<i; j++)
                      {
			temp = currentQueue.at(j);
			if (temp.Time<=j) //This part needs an extra condition, namely the TXattempt test.
			{
	                      txqueue.push_back(temp);
			}
		      }
                      return txqueue;
}

bool Frame::getFrameToTX(int i, Frame &frame)
{

if (frame.Time<=i)
return true;
else
return false;

}

bool Frame::checkFrameTXattempt(Frame &frame)
{
if (frame.TXattempt == 0)
return true;
else
return false;
}

bool Frame::checkFramePLR(Frame &frame)
{
if (frame.TXattempt == 10)
return true;
else
return false;
}

bool Frame::checkFrameMaxTX(Frame &frame)
{
if (frame.TXattempt == 4)
return true;
else
return false;
}

int Frame::GetTXattempt(Frame &frame)
{

return frame.TXattempt;

}

Frame Frame::ChangeStatusToTransmitted(Frame &frame)
{
		//frame.TXattempt=1;
		frame.TXattempt=frame.TXattempt + 1;
	return frame;
}

Frame Frame::ChangeStatusToDropped(Frame &frame)
{
		frame.TXattempt=10;
	return frame;
}

Frame Frame::SetFrameACKtoTrue(Frame &frame)
{
	frame.ACK=true;
	return frame;
}


int Frame::CheckStatusTX(Frame &frame)
{

return frame.TXattempt;

}

int Frame::CheckUserID(Frame &frame)
{

return frame.UserID;

}

int Frame::CheckFrameID(Frame &frame)
{

return frame.frameID;

}

int Frame::GetFrameSize(Frame &frame)
{

return frame.frameSize;

}

int Frame::CheckDelay(Frame &frame)
{

return frame.Time;

}

int Frame::GetDelay(Frame &frame)
{

return frame.Delay;

}

int Frame::GetTOS(Frame &frame)
{

return frame.TOS;

}

Frame Frame::SetDelay(Frame &frame, int FrameDelay)
{

frame.Delay = FrameDelay;

return frame;

}

bool Frame::CheckACK(Frame &frame)
{

if (frame.ACK == true)
	return true;
else
	return false;

}

int Frame::AssignRand(Frame &frame)
{
int HARQRand = 0;
time_t seconds;
time(&seconds);

srand((unsigned int) seconds);
//cout<<"Assign a random number to the frame"<<endl;
HARQRand = rand() % 100 + 1;
return HARQRand;
}


