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
#include "eNodeB.h"	
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
FILE *ResultsFile;

UserEquipment UE, tempUE;
ChannelQuality CQIndex;
Input InputFromCLI, CLIOptions;
eNodeB RFNode;

ResultsFile = fopen("CommaDelimitedOutput.txt","a");

int i = 0, time = 0, framecount = 0, UEcount = 0, FrameSeqNumber = 0, tempCQI = 0, j = 0;
int SimulationTime = 0;
int Scheduler;
int UEquipUserID, NumUsers = 0;
int UECandidateQueueSize = 0;
//int RelayCandidateQueueSize = 0;
int UEListSize = 0;
int FrameQueueSize = 0;
int TransmittedFramesSize = 0;
int FrameSize = 0;
int FrameDelay = 0;
int TXqueueSize = 0;
int FrameTXattempt = 0;
int frameTrackerSize = 0;
int DataRate = 0;
//int TotalTXFrames = 0;
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
int TotalRetransCount = 0;
int TotalDelay = 0;
int AverageDelay = 0;
//int countTX = 0;
int CellPart = 0;
int NumRN = 1;
div_t RNtransmitTTI;
int remainder = 0;

//float tempSINR;
float ReportedSINR = 0 ;
  vector<ChannelQuality> CQIDataBase;
  vector<Frame> PS, TXqueue, eNodeBbuffer, RNbuffer, RNTXqueue;
  vector<int> frameTracker;
  vector<int> UETracker;
  vector<Frame> TransmittedFrames;
  vector<UserEquipment> UEList, UECandidateQueue, TempUEQ, RelayCandidateQueue;
  vector<ResourceBlock> UERblocks;
  vector<eNodeB> RFNodeList;

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
			
//The below is the start of the setup for the relay node component.
//Note that NumRN is actually number of relays nodes +1.
//The next part is to slice up the cell users.
//Then can assign the relay node ID or the cell ID.
		CellPart = (NumUsers/NumRN) ;
		cout<<"Number of Users attaced to eNodeB = "<<CellPart<<" Number of Users attached to the Relay Node = "<<NumUsers - CellPart<<endl;
		if (i < CellPart)
			UE.SeteNodeB(UEList.at(i));
		else
			UE.SetRelayNode(UEList.at(i));

		//int UserID = 0;
		UE.ShowNodeStatus(UEList.at(i));
		for (i = 1; i< FrameQueueSize; i++)
		{
			//if (frameQueue.CheckUserID(PS.at(i) < CellPart))
			//UserID = frameQueue.CheckUserID(PS.at(i));
			if ( frameQueue.CheckUserID(PS.at(i))< CellPart)
				eNodeBbuffer.push_back(PS.at(i));
			else 
				RNbuffer.push_back(PS.at(i));

		}

int eNodeBbuffersize, RNbuffersize;

		eNodeBbuffersize = eNodeBbuffer.size();
		RNbuffersize = RNbuffer.size();
		cout<<"Total number of frames = "<<FrameQueueSize<<" RN queue size = "<<RNbuffersize<<" eNodeB queue size = "<<eNodeBbuffersize<<endl;
		//NumUsers = NumUsers - (NumUsers/8);
//Need to split up the PS maybe so that some go into the queue for relay node.
//I think maybe at the start; assign some users to a relay node, the second lot to the eNodeB.
//Then every 8ttis, need to build up the tx queue to send to the relay node.
//
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
		if (i < CellPart)
			UE.SeteNodeB(UEList.at(i));
		else if ((i >= CellPart) && i <NumUsers)
			UE.SetRelayNode(UEList.at(i));
//Once we set this up, I think we should loop through the PS queue and create the relaynode buffer.
//

		UE.ShowNodeStatus(UEList.at(i));
		//Need to put something in about here that delineates whether the UE is attached to a relay node 
		//or an eNodeB.
		//Suggest to use a midpoint type statement;
		//so midpoint = NumUsers/2
		//if i> midpoint then set it as relaynode else set it as eNodeB.
		//
			//if (i < CellPart)
			//	UE.SeteNodeB()	
			//
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

		

      		cout<<"queue size = "<<PS.size()<<endl;	

		for (time=0; time<SimulationTime; time++) //TTI loop.
		{
			//the below block of code is required each TTI.  It runs through each frame to work out
			//which UEs have frames to be transmitted.
			UEListSize = UEList.size();
			RNtransmitTTI = div (time,8);
			remainder = RNtransmitTTI.rem;
			if ( remainder == 0)
			{
				cout<<"Transmitting to Relay Node"<<endl; 
				//Send frames at that point to RN.
				
			}
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
					cout<<"SINR = "<<ReportedSINR<<" dB.  DataRate = "<<DataRate<<endl;
					UEList.at(UEcount) = UE.addCQI(UEList.at(UEcount), tempCQI);

					UEList.at(UEcount) = UE.addRate(UEList.at(UEcount), DataRate);
					 //UE.ShowNodeStatus(UEList.at(UEcount));
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
				//FrameDelay = time - frameQueue.CheckDelay(PS.at(i));
				//FrameDelay = frameQueue.CheckDelay(PS.at(i));
				//Need to now add this into the frame field.
				//
				//I think the below show have the second condition replaced with a check on whether an ACK has been received.
				//Though alos need a check on TX attempt.  Perhaps that could be a second if.
				//so would be if ((...) && frameQueue.CheckACK(PS.at(i)) then if TXattemppt ok then go.
				//if (frameQueue.getFrameToTX(time,PS.at(i)) && frameQueue.checkFrameTXattempt(PS.at(i)))
				//
				//
				//New feature to add in for relay nodes:  Need to check each frame's UE, then see
				//if is attached to a eNodeB or a RN.
				//Put it in the second iff statement.  Push the frame eitehr onto
				//the TXqueue or onto the RNnode buffer.
				FrameTXattempt = frameQueue.GetTXattempt(PS.at(i));
				//Fix the FrameTXattempt - don't leave a number in.
				if (frameQueue.getFrameToTX(time,PS.at(i)) && !frameQueue.CheckACK(PS.at(i)) && (FrameTXattempt <5))//frameQueue.checkFrameTXattempt(PS.at(i)))
				{
					FrameDelay = time - frameQueue.CheckDelay(PS.at(i));
					//cout<<"Frame delay is "<<FrameDelay<<endl;
					//if (((time - FrameDelay) < 200) ) //Set the 200 as a const - a delay threshold
					if (frameQueue.GetTOS(PS.at(i)) == 0)
					{
						TXqueue.push_back(PS.at(i));
                                                frameTracker.push_back(i);
					} else if ((frameQueue.GetTOS(PS.at(i)) == 1) && (FrameDelay < 250)) //Set the 200 as a const - a delay threshold
					{
						TXqueue.push_back(PS.at(i));	
						frameTracker.push_back(i);  
					} else if  ((frameQueue.GetTOS(PS.at(i)) == 1) && (FrameDelay >=250))
					{
						frameQueue.ChangeStatusToDropped(PS.at(i));
						TotalPLRFrames++;
						cout<<"Total PLR frames at time  = "<<time<<" is "<<TotalPLRFrames<<endl;
						//Don't process any further.
					}
				}

			
			}

			//Check we have some UEs first.
			if (UECandidateQueue.size()>0)
			{
			//Schedule UEs.  Note that this will have extra parts for the relaynodes.
			//If the time div 8 == 0, then we need to add more frames
			//to the relay node queue.
				if (Scheduler == 1)
				{
					UECandidateQueue = UE.MaxRate(UECandidateQueue);
					UECandidateQueueSize = UECandidateQueue.size();
					//RelayCandidateQueue = UE.MaxRate(RelayCandidateQueue);
					//RelayCandidateQueueSize = RelayCandidateQueue.size();
				}
				else if (Scheduler == 2)
				{
					UECandidateQueue = UE.ProportionalFair(UECandidateQueue);
					UECandidateQueueSize = UECandidateQueue.size();
					//RelayCandidateQueue = UE.ProportionalFair(RelayCandidateQueue);
					//RelayCandidateQueueSize = RelayCandidateQueue.size();
				}
				for (UEcount = 0; UEcount<UECandidateQueueSize; UEcount ++)
				{
					//loop through each UE RB in the queue.
					UEquipUserID = UE.GetUEquipmentUserID(UECandidateQueue.at(UEcount));
					
					TXqueueSize = TXqueue.size();
					//Loop through the TX queue.  When we find a matching User number,
					//check the frames to see if they have been transmitted yet.
					//Initially they will not have been.
					for (framecount = 0; framecount<TXqueueSize; framecount++)
					{
						temp=TXqueue.at(framecount);
						FrameTXattempt = frameQueue.GetTXattempt(temp);
						FrameSeqNumber = frameTracker.at(framecount);
						//cout<<"At start of for loop.  framecount = "<<framecount<<endl;
					 	if (FrameTXattempt == 0)	
						{
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
								//There is a bug in this part of the code.  Issue is that the 
								//frames get transmitted in the next resourc block.
								//Probably need to change the TX status.  Need an in flight status.
								//Or need another iff statement.
								//I think the PS update below is ok.
								//Maybe have an if StatusTX TX queue == 0 then do the transmission.  Otherwsie, nothing.
								//FrameTXattempt = frameQueue.GetTXattempt(temp);
								//cout<<"TX attempt = "<<FrameTXattempt<<endl;
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
								//FrameSeqNumber = frameTracker.at(framecount);
								PS.at(FrameSeqNumber) = frameQueue.ChangeStatusToTransmitted(PS.at(FrameSeqNumber));
								//}
								//cout<<"Rate is now "<<UE.ShowRate(UECandidateQueue.at(UEcount))<<endl;
							}   
						   }
						} else
						{
								DebugNonTXRB++;
							//cout<<"Done.  Frame SeqNumber "<<FrameSeqNumber<<" could not be transmitted"<<endl;
							//cout<<"Done.  Printing out frames ..."<<endl;
							//cout<<"Done."<<endl;
						}
					}
	
				}
			}
			//A summary of what has been don ein this TTI.
			cout<<"Candidate Queue size after scheduling = "<<UECandidateQueueSize<<endl;
			cout<<"TX Queue size = "<<TXqueueSize<<endl;
			frameTrackerSize = frameTracker.size();
			cout<<"Frame Tracker size = "<<frameTrackerSize<<endl;
			cout<<"Frames Transmitted in the UE loop = "<<DebugTXRB<<endl;
			cout<<"Frames NOT Transmitted in the UE loop = "<<DebugNonTXRB<<endl;

			
			//TXqueueSize = TXqueue.size();
			//
			//This is the transmission part.
			//so we set the frame transmission attempt to 1 here.
			//This is not so great, as the TX attemp could be 2 as well.
			//Need to fix this in future code versions.
			//
			//Stick the below code in the TX section above.
			cout<<"FrameTrackerSize = "<<frameTrackerSize<<endl;
			framecount = 0;
			//for (framecount = 0; framecount<frameTrackerSize; framecount++)
			for (framecount = 0; framecount<TXqueueSize; framecount++)
			{
				FrameSeqNumber=frameTracker.at(framecount);
				FrameTXattempt = frameQueue.GetTXattempt(PS.at(FrameSeqNumber));
				if (FrameTXattempt >0) //frameTracker.at(framecount) != -1) //Put in extra check on whether frame is in transmittedFrames?
				{
				//FrameSeqNumber=frameTracker.at(framecount);
				//Maybe set it to frame Tracker instead
				tempFrame=PS.at(FrameSeqNumber);
				AssignRand = frameQueue.AssignRand(tempFrame); 
					if (AssignRand > 5)
					{
						tempFrame=frameQueue.SetFrameACKtoTrue(tempFrame);
						//Delay calculation goes here
						FrameDelay=time - frameQueue.CheckDelay(tempFrame);
						tempFrame=frameQueue.SetDelay(tempFrame, FrameDelay);
						PS.at(FrameSeqNumber)=tempFrame;
						TotalACKFrames++;
					}
					else if (AssignRand <=0)
					{
						TotalNACKcount++;
					}	
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
		} //End of the TTI loop.




		
		TransmittedFramesSize = TransmittedFrames.size();


		//cout<<"Total transmitted frames are "<<TotalTXFrames<<endl;
		cout<<"Total transmitted frames are "<<TransmittedFramesSize<<endl;
		cout<<"Total number of frames are "<<FrameQueueSize<<endl;
		cout<<"Total number of ACK frames are "<<TotalACKFrames<<endl;
		TotalACKFrames = 0;
		//
		//Now run through the PS queue and see how many were transmitted, how many got an ACK or a NACK.
		//Then add each up.  Should be able to get a summary.

		//int TXSuccess = 0;
		 cout<<"Total PLR frames before count are "<<TotalPLRFrames<<endl;
		TotalPLRFrames = 0;
		for (i=1; i<FrameQueueSize; i++)
		{
			//if (frameQueue.CheckACK(PS.at(i)))
			//	TotalACKFrames = TotalACKFrames + frameQueue.GetFrameSize(PS.at(i));
			////////Not sure what the above is meant to do!!!!
			if (frameQueue.CheckACK(PS.at(i)))// && (frameQueue.CheckStatusTX(PS.at(i)) > 0))
			{
				//frameQueue.getFrameInfo(PS.at(i));
				TotalACKFrames++;
				tempTput = frameQueue.GetFrameSize(PS.at(i));
				Throughput = Throughput + tempTput;
				TotalDelay = TotalDelay + frameQueue.GetDelay(PS.at(i));
				//cout<<"Throughput = "<<Throughput<<" TotalACKFrames = "<<TotalACKFrames<<endl;
				
			}
			if (frameQueue.checkFramePLR(PS.at(i)))
				TotalPLRFrames++;
				//TotalPLRFrames = TotalPLRFrames + 1;
			if (!frameQueue.CheckACK(PS.at(i)) && frameQueue.checkFrameMaxTX(PS.at(i)))
				TotalMaxTXFrames++;
			if ((frameQueue.GetTXattempt(PS.at(i)) >1) && (frameQueue.GetTXattempt(PS.at(i))< 5))
				TotalRetransCount++;
				//TotalMaxTXFrames = TotalMaxTXFrames + 1;
		}
		/*cout<<"Total Throughput is "<<(Throughput/SimulationTime)<<endl;
		cout<<"Total ACK frames are "<<(TotalACKFrames/SimulationTime)<<endl;
		cout<<"Total NACK frames are "<<(TotalNACKcount/SimulationTime)<<endl;
		cout<<"Total PLR frames are "<<(TotalPLRFrames/SimulationTime)<<endl;
		cout<<"Total MaxTX frames are "<<(TotalMaxTXFrames/SimulationTime)<<endl;
		*/
		AverageDelay=TotalDelay/TotalACKFrames;	
		cout<<"Total Throughput is "<<Throughput<<endl;
		cout<<"Total delay is "<<TotalDelay<<endl;
		cout<<"Average delay is "<<TotalDelay/TotalACKFrames<<endl;
		cout<<"Total ACK frames are "<<TotalACKFrames<<endl;
		cout<<"Total NACK frames are "<<TotalNACKcount<<endl;
		cout<<"Total PLR frames are "<<TotalPLRFrames<<endl;
		cout<<"Total MaxTX frames are "<<TotalMaxTXFrames<<endl;

//Write the results to a file in comman delimited format.  Should maybe change this to space delimited.
		fprintf (ResultsFile, "%d,%d,%d,%d,%d,%d,%d,%d \n",NumUsers,SimulationTime,Scheduler,Throughput,AverageDelay,TotalPLRFrames,TransmittedFramesSize,TotalRetransCount);
		fclose(ResultsFile);
	
  return 0;
}
