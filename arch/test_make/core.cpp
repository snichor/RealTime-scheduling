#include <iostream>
#include <vector>
#include <fstream>
#include "frame.h"	
#include "user.h"	
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
Frame frameQueue, temp;   
FILE *DataFile;
FILE *UEFile;
UserEquipment UE;

int i = 0, j= 0;
  vector<Frame> PS, TXqueue;

  vector<UserEquipment> UEList;
  UEList = UE.ReadInUE(UEFile);

	frameQueue.frameInit(frameQueue);

		PS=frameQueue.enqueueFrame(DataFile);  
      		cout<<"i = "<<i<<endl;	
      		cout<<"queue size = "<<PS.size()<<endl;	
		//for (i=0; i<(PS.size()); i++)
		//for (i=0; i<100; i++)
		for (i=0; i<(PS.size()); i++)
		{
			for (j=0; j<200; j++)
			{
//
//Here we need to set an if statement for time less than or equal to a certain amount.
//then we can fetch all the frames required to be transmitted.
//The idea is that we build a queue at that time, so need to di a push statement.
//
//			So we will need a new access function that returns a queue.
//			It is a bit like the getFrameInfo, but it will return another queue.
//			So call the function GetFramesForTX(i)
//			declaration will be
//
//			vector<Frame> GetFrameForTX(i, framequeue)
//			for (j=0; j++, j<i
//			do
//			txqueue=framequeue.at(j)
//			 return txqeueu
//
//			I am not sure if this is the best way to do this.
//			The second part is tricky too.  Need to also get the list of UEs.
      			//frameQueue.getFrameInfo(PS.at(i));
      			//frameQueue.getFrameInfo(PS.at(i));
      			//frameQueue.getFrameInfo(PS.at(i));
		//TXqueue=frameQueue.GetFrameForTX(i,PS);	
		temp=PS.at(i);
		//
		//If the frame sent to getFrameToTX is less than t than add it to the queue.  
		//This is not that sophisticated yet, as we would probably look to check on frames 
		//transmitted previously, and delete them first.
		//We would need to check which frame had a problem.
		//Note that this is a contrived example; t is set to 100.
		//But the idea is that we check frames up to 100.
		//Probably anything less would be dropped anyway.
		//
		//So the idea is to transmit the frames, but first, check on the status of
		//transmitted frames.  So a transmitted frame queue is built up;
		//basically, this will have the frame id, transmission time, and whether it
		//got an ACK or a NACK.  If it gets an ACK, then remove it from the main transmission
		//queue.  If not, check and see how many retrans it has had, and possibly
		//schedule it again.
		//
		//
		//In any case, here we push the frame onto the queue.
		if (frameQueue.getFrameToTX(j,temp))
			TXqueue.push_back(temp);	
			}	
		}
      		cout<<"queue size = "<<TXqueue.size()<<endl;	
		for (i=0; i<(TXqueue.size()); i++)
      			frameQueue.getFrameInfo(TXqueue.at(i));
//Next step is to have a packet scheduler select frames from this.  After transmission, then the frames
//can be removed.
//
	
  return 0;
}
