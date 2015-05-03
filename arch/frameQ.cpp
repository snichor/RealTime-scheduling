#include <iostream>
#include <vector>
#include <fstream>
#include "frame.h"	
using namespace std;

//
//
//main program
//
//
//
//
int main ()
{
Frame frameQueue;   
FILE *DataFile;
int i = 0, j= 0;
  vector<Frame> PS;
	frameQueue.frameInit(frameQueue);

		PS=frameQueue.enqueueFrame(DataFile);  
      		cout<<"i = "<<i<<endl;	
      		cout<<"queue size = "<<PS.size()<<endl;	
		for (i=0; i<(PS.size()); i++)
		{
      			frameQueue.getFrameInfo(PS.at(i));
		}	
  return 0;
}
