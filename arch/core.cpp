#include <iostream>
#include <vector>
#include <fstream>
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include "frame.h"	
#include "user.h"	
#include "PacketScheduler.h"	
#include "ChannelQuality.h"	
#include "CLI.h"	
using namespace std;

//
//
//main program
//
//
//
//
int main (int argc, char *argv[])
{
Frame frameQueue, temp, tempFrame; 
FILE *DataFile;
FILE *UEFile;
FILE *SINRFile;

UserEquipment UE, tempUE;
ChannelQuality CQIndex;
Input InputFromCLI, CLIOptions;

//int i = 0, j= 0, k = 0, time = 0, framecount = 0, UEcount = 0, TXcount = 0, FrameSeqNumber = 0, tempCQI = 0;
int i = 0, time = 0, framecount = 0, UEcount = 0, FrameSeqNumber = 0, tempCQI = 0, j = 0;
int SimulationTime = 0;
int Scheduler;
int UEquipUserID, NumUsers = 0;
int UECandidateQueueSize = 0;
int UEListSize = 0;
int FrameQueueSize = 0;
int TransmittedFramesSize = 0;
int FrameSize = 0;
int FrameDelay = 0;
int TXqueueSize = 0;
int FrameTXattempt = 0;
int frameTrackerSize = 0;
int DataRate = 0;
int TotalTXFrames = 0;
int TotalACKFrames = 0;
int TotalPLRFrames = 0;
int TotalNACKcount = 0;
int TotalMaxTXFrames = 0;
int Throughput = 0;
int TempUEQSize = 0;
int SumDataRate = 0;
int UEtime = 0;
//int UETrackerSize = 0;
int RBCount = 0;
int AssignRand = 0;
int DebugTXRB = 0;
int DebugNonTXRB = 0;
int tempTput = 0;

//float tempSINR;
float ReportedSINR = 0 ;
  vector<ChannelQuality> CQIDataBase;
  vector<Frame> PS, TXqueue;
  vector<int> frameTracker;
  vector<int> UETracker;
  vector<Frame> TransmittedFrames;
  vector<UserEquipment> UEList, UECandidateQueue, TempUEQ;
  vector<ResourceBlock> UERblocks;

	CLIOptions=InputFromCLI.GetInput(argc, argv);
	NumUsers = CLIOptions.GetNumberOfUsers(CLIOptions);
	SimulationTime = CLIOptions.GetSimulationTime(CLIOptions);
	Scheduler = CLIOptions.GetPacketScheduler(CLIOptions);


	cout<<"Number of Users is "<<NumUsers<<endl;
	cout<<"Simulation Time is "<<SimulationTime<<endl;
//First we need to check the options given.
//Call the function taht will read in the CLI variables.
//
	
	SINRFile = fopen("../data/SINR.txt","r");
	if (SINRFile!=NULL)
	{
	CQIDataBase=CQIndex.ReadInLimits(SINRFile);
	cout<<"read in limits"<<endl;
	fclose(SINRFile);
	}
	else
	{
	cout<<"Cannot open SINR file"<<endl;
	return 1;
	}

 	UEFile = fopen("../data/mpgains1_100.txt","r");
	if (UEFile!=NULL)
	{
	UEList = UE.ReadInUE(UEFile, NumUsers);
	fclose(UEFile);
	UEListSize = UEList.size();
	}
	else
	{
	cout<<"Cannot open UE file"<<endl;
	return 1;;
	}

	frameQueue.frameInit(frameQueue);

 	DataFile= fopen("../data/data.txt","r");	
	if (DataFile!=NULL)
	{
	PS=frameQueue.enqueueFrame(DataFile, NumUsers);  
 	fclose(DataFile);
	FrameQueueSize = PS.size();
	}
	else
	{
	cout<<"Cannot open frame file"<<endl;
	return 1;
	}

//OK, need to move the loop for calculation of data rate, adding CQI, etc
//into the area below.
//And I think the outer loop needs to be a user loop.
//We need to then loop through the UEList (which is a vector)
//and for each UE, check the RB number.  Which means a further loop, I think.
//so first check for the user number.
//ok, we have a match.
//now which RB are we after?
//ok, maybe the RB loop has gotta be checked
			for (UEcount=0; UEcount<UEListSize; UEcount++)
			{
					ReportedSINR = UE.GetSINR(UEList.at(UEcount));

					tempCQI=CQIndex.FindCQI(ReportedSINR, CQIDataBase);
					
					DataRate = CQIndex.FindRate(ReportedSINR, CQIDataBase);
					//Now that we have the data rate, update the average data rate.
					//
					UEList.at(UEcount) = UE.addCQI(UEList.at(UEcount), tempCQI);

					UEList.at(UEcount) = UE.addRate(UEList.at(UEcount), DataRate);
					//UECandidateQueue.push_back(UEList.at(UEcount));

			}
			
		for (i = 1; i<=NumUsers; i++)
		{
			for (UEcount=0; UEcount<UEListSize; UEcount++)
			{
				if (UE.ShowUserID(UEList.at(UEcount)) == i)
				{
					TempUEQ.push_back(UEList.at(UEcount));
					UETracker.push_back(UEcount);
					
				}
			}
			
			TempUEQSize = TempUEQ.size();
			for (RBCount=0; RBCount<25; RBCount++)
			{
				for (j=0; j<TempUEQSize; j++)
				{
					if (UE.ShowRB(TempUEQ.at(j)) == RBCount)
						{
							//cout<<"Matched an RB"<<endl;
							//cout<<"SumDataRate = "<<SumDataRate<<endl;
							SumDataRate = SumDataRate + UE.ShowRate(TempUEQ.at(j));
							TempUEQ.at(j) = UE.UpdateSumRate(TempUEQ.at(j), SumDataRate);
							UEtime = UE.ShowTime(TempUEQ.at(j));
							TempUEQ.at(j) = UE.UpdateAverageRate(TempUEQ.at(j), UEtime);
							UEList.at(UETracker.at(j)) = TempUEQ.at(j);
							//And also need to grab the tracker j value and update
							//the UEList.
							//
						}	
						//cout<<"SumDataRate = "<<SumDataRate<<endl;
						//cout<<"AverageData
				}
				//cout<<"SumDataRate = "<<SumDataRate<<endl;
				SumDataRate = 0;
			}	
	

			TempUEQ.clear();
			UETracker.clear();	
		}

		//Below is commented out for the moment.  It is being used for debugging. 16/9/12
		/*for (UEcount=0; UEcount<UEListSize; UEcount++)
			UE.getUEInfo(UEList.at(UEcount));
		*/	

		

      		cout<<"queue size = "<<PS.size()<<endl;	

		for (time=0; time<SimulationTime; time++) //TTI loop.
		{
			//the below block of code is required each TTI.  It runs through each frame to work out
			//which UEs have frames to be transmitted.
			UEListSize = UEList.size();
			//for (UEcount=0; UEcount<UEList.size(); UEcount++)
			for (UEcount=0; UEcount<UEListSize; UEcount++)
			{
				if (UE.getCandidateUE(time, UEList.at(UEcount))) //Maybe change a little; get the UE time and do a time == ue.getTime().
				{

					//tempCQI=UE.getCQI(UEList.at(UEcount));
					//cout<<"CQI = "<<tempCQI<<endl;
					//Probably need to set the data rate here too.
					ReportedSINR = UE.GetSINR(UEList.at(UEcount));
					tempCQI=CQIndex.FindCQI(ReportedSINR, CQIDataBase);
					//cout<<"Second call has CQI = "<<tempCQI<<endl;
					DataRate = CQIndex.FindRate(ReportedSINR, CQIDataBase);
					//Now that we have the data rate, update the average data rate.
					//cout<<"SINR = "<<ReportedSINR<<" dB.  DataRate = "<<DataRate<<endl;
					UEList.at(UEcount) = UE.addCQI(UEList.at(UEcount), tempCQI);

					UEList.at(UEcount) = UE.addRate(UEList.at(UEcount), DataRate);
					//Need to now update the averege data rate.
					//UEList.at(UEcount) = UE.UpdateAverageRate(UEList.at(UEcount), DataRate);
					UECandidateQueue.push_back(UEList.at(UEcount));
				}

			}

			//for (i=0; i<(PS.size()); i++) 
			for (i=0; i<FrameQueueSize; i++) 
			{

				temp=PS.at(i);
				//This block builds a list of candidate frames for transmission.
				//Need to add an extra if; if the frame has not been in the queue more than 200TTI for instance.
				//This can be set via a CLI option.
				FrameDelay = frameQueue.CheckDelay(PS.at(i));
				//I think the below show have the second condition replaced with a check on whether an ACK has been received.
				//Though alos need a check on TX attempt.  Perhaps that could be a second if.
				//so would be if ((...) && frameQueue.CheckACK(PS.at(i)) then if TXattemppt ok then go.
				//if (frameQueue.getFrameToTX(time,PS.at(i)) && frameQueue.checkFrameTXattempt(PS.at(i)))
				FrameTXattempt = frameQueue.GetTXattempt(PS.at(i));
				//Fix the FrameTXattempt - don't leave a number in.
				if (frameQueue.getFrameToTX(time,PS.at(i)) && !frameQueue.CheckACK(PS.at(i)) && (FrameTXattempt <5))//frameQueue.checkFrameTXattempt(PS.at(i)))
				{
					if ((time - FrameDelay) < 200) //Set the 200 as a const - a delay threshold
					{
						TXqueue.push_back(PS.at(i));	
						frameTracker.push_back(i);  
					} else
					{
						cout<<"Packet dropped at time "<<time<<endl;
						frameQueue.ChangeStatusToDropped(PS.at(i));
						frameQueue.getFrameInfo(PS.at(i));
						//Don't process any further.
					}
				}

			
			}

			cout<<"Candidate Queue size before scheduling= "<<UECandidateQueue.size()<<endl;
			//Check we have some UEs first.
			if (UECandidateQueue.size()>0)
			{
				if (Scheduler == 1)
				{
					UECandidateQueue = UE.MaxRate(UECandidateQueue);
					cout<<"MaxRate scheduling done.  UEs scheduled at time "<<time<<" are as below:"<<endl;
					UECandidateQueueSize = UECandidateQueue.size();
				}
				else if (Scheduler == 2)
				{
					UECandidateQueue = UE.ProportionalFair(UECandidateQueue);
					cout<<"PF scheduling done.  UEs scheduled at time "<<time<<" are as below:"<<endl;
					UECandidateQueueSize = UECandidateQueue.size();
				}
				for (UEcount = 0; UEcount<UECandidateQueueSize; UEcount ++)
				{
					UE.getUEInfo(UECandidateQueue.at(UEcount));
					UEquipUserID = UE.GetUEquipmentUserID(UECandidateQueue.at(UEcount));
					
					TXqueueSize = TXqueue.size();
					for (framecount = 0; framecount<TXqueueSize; framecount++)
					{
						temp=TXqueue.at(framecount);
						if (frameQueue.CheckUserID(temp) == UEquipUserID)
						{
							//Get the frame size.  Check the RB.
							//Check that the datarate can support the frame.
							//If so, then send the frame size to the decrement function
							//to reduce the allowed frames for TX.
							//Then we can set status to transmitted.
							tempUE = UECandidateQueue.at(UEcount);
							FrameSize = frameQueue.GetFrameSize(temp);
							if (UE.ShowRate(UECandidateQueue.at(UEcount))> FrameSize)		
							{
								//Need to actually add 1 to the TX, rather than change status.
								//TXqueue.at(framecount)=frameQueue.ChangeStatusToTransmitted(TXqueue.at(framecount));
								TXqueue.at(framecount)=frameQueue.ChangeStatusToTransmitted(temp);
								DebugTXRB++;
								//frameQueue.SetFrameACKtoTrue(TXqueue.at(framecount));
								//cout<<"Decrementing Rate"<<endl;
								//cout<<"FrameSize = "<<FrameSize<<endl;
								//Need to put a frame seq number somewhere in here.
								UECandidateQueue.at(UEcount) = UE.DecrementRate(tempUE, FrameSize);	
								TransmittedFrames.push_back(TXqueue.at(framecount));
								//I think the PS queue should probably be updated here too.
								FrameSeqNumber = frameTracker.at(framecount);
								PS.at(FrameSeqNumber) = frameQueue.ChangeStatusToTransmitted(PS.at(FrameSeqNumber));
								//cout<<"Rate is now "<<UE.ShowRate(UECandidateQueue.at(UEcount))<<endl;
							} else  
							{
								DebugNonTXRB++;
								frameTracker.at(framecount)= -1;
							}
						}
					}
	
				}
			}
			cout<<"Candidate Queue size after scheduling = "<<UECandidateQueue.size()<<endl;
			cout<<"Candidate Queue size after scheduling = "<<UECandidateQueueSize<<endl;
			cout<<"TX Queue size = "<<TXqueue.size()<<endl;
			cout<<"TX Queue size = "<<TXqueueSize<<endl;
			frameTrackerSize = frameTracker.size();
			cout<<"Frame Tracker size = "<<frameTracker.size()<<endl;
			cout<<"Frame Tracker size = "<<frameTrackerSize<<endl;
			cout<<"Frames Transmitted in the UE loop = "<<DebugTXRB<<endl;
			cout<<"Frames NOT Transmitted in the UE loop = "<<DebugNonTXRB<<endl;

			
			TXqueueSize = TXqueue.size();
			//for (framecount=0; framecount<TXqueue.size(); framecount++)
			//Below is to mark all frames that were in the candidate queue
			//that were not scheduled.
			framecount = 0;
			int DebugTXFrames = 0, DebugNonTxFrames = 0;
			for (framecount=0; framecount<TXqueueSize; framecount++)
			{
				if (frameTracker.at(framecount) != -1) //Need extra condition in here.  Need to check TX queue as well?  Or PS? 
				{
					//frameTracker.at(framecount)= -1;
					DebugTXFrames++;
				} else
				{
					DebugNonTxFrames++;
				}
			}
			cout<<"DEBUG: Frames NOT Transmitted = "<<DebugNonTxFrames<<endl;
			cout<<"DEBUG: Frames Transmitted = "<<DebugTXFrames<<endl;	
			//
			//for (framecount = 0; framecount<frameTracker.size(); framecount++)
			//This is the transmission part.
			//so we set the frame transmission attempt to 1 here.
			//This is not so great, as the TX attemp could be 2 as well.
			//Need to fix this in future code versions.
			cout<<"FrameTrackerSize = "<<frameTrackerSize<<endl;
			framecount = 0;
			//for (framecount = 0; framecount<frameTrackerSize; framecount++)
			for (framecount = 0; framecount<TXqueueSize; framecount++)
			{
				if (frameTracker.at(framecount) != -1) //Put in extra check on whether frame is in transmittedFrames?
				{
				FrameSeqNumber=frameTracker.at(framecount);
				//cout<<"Frame Seq Number = "<<FrameSeqNumber<<endl;	
				//Maybe set it to frame Tracker instead
				tempFrame=PS.at(FrameSeqNumber);
				AssignRand = frameQueue.AssignRand(tempFrame); 
				//AssignRand = frameQueue.AssignRand(PS.at(FrameSeqNumber)); 
					if (AssignRand > 0)
					{
						tempFrame=frameQueue.SetFrameACKtoTrue(tempFrame);
						PS.at(FrameSeqNumber)=tempFrame;
						//PS.at(FrameSeqNumber)=frameQueue.SetFrameACKtoTrue(PS.at(FrameSeqNumber));
						TotalACKFrames++;
					//cout<<"ACK received"<<endl;
					}
					else if (AssignRand <=0)
					{
						TotalNACKcount++;
					//cout<<"NACK received = "<<TotalNACKcount<<endl;
					//Nothing else as yet to do
					}	
				//TotalTXFrames++;
				//PS.at(FrameSeqNumber)=frameQueue.ChangeStatusToTransmitted(PS.at(FrameSeqNumber));
				//Commented eblow out for Debugging.
				//PS.at(FrameSeqNumber)=frameQueue.ChangeStatusToTransmitted(tempFrame);
				//the frame has been transmitted in any case.
				//Commented out below as the program is moving towards prod.  Need to write below output to a file.
				//frameQueue.getFrameInfo(PS.at(FrameSeqNumber));	
				}
			}	

			//
				cout<<"TotalACKFrames after looping through FT = "<<TotalACKFrames<<endl;
			//Clear the queues, ready for next TTI. 
			DebugTXRB = 0;
			DebugNonTXRB = 0;
			TotalACKFrames = 0;
			TXqueue.clear();
			frameTracker.clear();
			UECandidateQueue.clear();
		}




		
		TransmittedFramesSize = TransmittedFrames.size();

		//Below lines commented out for the moment.  Need to change this so it writes out to a file.
		//for (i=1; i<FrameQueueSize; i++)
      		//	frameQueue.getFrameInfo(PS.at(i));

		for (i = 1; i<TransmittedFramesSize; i++)
		{
			//frameQueue.getFrameInfo(TransmittedFrames.at(i));
			//TotalTXFrames = TotalTXFrames + frameQueue.GetFrameSize(TransmittedFrames.at(i));
			TotalTXFrames++;
		}

		cout<<"Total transmitted frames are "<<TotalTXFrames<<endl;
		cout<<"Total number of frames are "<<FrameQueueSize<<endl;
		cout<<"Total number of ACK frames are "<<TotalACKFrames<<endl;
		TotalACKFrames = 0;
		//
		//Now run through the PS queue and see how many were transmitted, how many got an ACK or a NACK.
		//Then add each up.  Should be able to get a summary.

		for (i=1; i<FrameQueueSize; i++)
		{
			//if (frameQueue.CheckACK(PS.at(i)))
			//	TotalACKFrames = TotalACKFrames + frameQueue.GetFrameSize(PS.at(i));
			////////Not sure what the above is meant to do!!!!
			if (frameQueue.CheckACK(PS.at(i)) && (frameQueue.CheckStatusTX(PS.at(i)) > 0))
			{
				//frameQueue.getFrameInfo(PS.at(i));
				TotalACKFrames++;
				tempTput = frameQueue.GetFrameSize(PS.at(i));
				Throughput = Throughput + tempTput;
				//cout<<"Throughput = "<<Throughput<<" TotalACKFrames = "<<TotalACKFrames<<endl;
				
			}
			if (frameQueue.checkFramePLR(PS.at(i)))
				TotalPLRFrames++;
				//TotalPLRFrames = TotalPLRFrames + 1;
			if (!frameQueue.CheckACK(PS.at(i)) && frameQueue.checkFrameMaxTX(PS.at(i)))
				TotalMaxTXFrames++;
				//TotalMaxTXFrames = TotalMaxTXFrames + 1;
		}
		/*cout<<"Total Throughput is "<<(Throughput/SimulationTime)<<endl;
		cout<<"Total ACK frames are "<<(TotalACKFrames/SimulationTime)<<endl;
		cout<<"Total NACK frames are "<<(TotalNACKcount/SimulationTime)<<endl;
		cout<<"Total PLR frames are "<<(TotalPLRFrames/SimulationTime)<<endl;
		cout<<"Total MaxTX frames are "<<(TotalMaxTXFrames/SimulationTime)<<endl;
		*/
		
		cout<<"Total Throughput is "<<Throughput<<endl;
		cout<<"Total ACK frames are "<<TotalACKFrames<<endl;
		cout<<"Total NACK frames are "<<TotalNACKcount<<endl;
		cout<<"Total PLR frames are "<<TotalPLRFrames<<endl;
		cout<<"Total MaxTX frames are "<<TotalMaxTXFrames<<endl;
	
  return 0;
}
