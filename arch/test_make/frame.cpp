// Inital coding  11/6/2012.
// Modified 23/6/2012.
// Modified enqueueFrame function to take a file as an argument.
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdio>
#include "frame.h"
using namespace std;
//
//function declarations
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

vector<Frame> Frame::enqueueFrame(FILE *InputFile)
{
Frame frame; 
vector<Frame> PS;
int time = 0, user = 0, pd = 0, pid = 0, psize = 0, stype = 0;
	InputFile = fopen("data.txt","r");
	while (!feof(InputFile)) 
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
		frame.TOS = stype;
	 PS.push_back(frame);
 	}	
	fclose(InputFile);
return PS;

}

void Frame::getFrameInfo(Frame &frame)
{

	cout<<"Time = "<<frame.Time<<" Packet Descriptor = "<<frame.PD<<" Frame ID = "<<frame.frameID<<" Frame Size = "<<frame.frameSize<<" User ID = "<<frame.UserID<<" Service type = "<<frame.TOS<<endl;
}


vector<Frame> Frame::GetFrameForTX(int i, vector<Frame> &currentQueue)
{
//Change what is passed to a frame, from a vector
int j=0;
vector<Frame> txqueue;
Frame temp;
			cout<<"i in function = "<<i<<endl;
                      for (j=0; j<i; j++)
                      {
			temp = currentQueue.at(j);
			if (temp.Time<=j)
			{
			//	cout<<"Got to if"<<endl; 
	                      txqueue.push_back(temp);
			}
		      }
                      return txqueue;
//
}

bool Frame::getFrameToTX(int i, Frame &frame)
{

if (frame.Time<i)
return true;
else
return false;

}
