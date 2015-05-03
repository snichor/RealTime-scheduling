#include <iostream>
#include <vector>
#include <cmath>
#include "user.h"
#include "frame.h"
using namespace std;
//
//function declarations
//
//

vector<UserEquipment> UserEquipment::ReadInUE(FILE *UEList, int NumUsers)
{
UserEquipment UE;
vector<UserEquipment> UERegister;
int UID = 0, timearrived = 0, RB = 0, count = 0;
float SigNoise;
	//cout<<"SINR = "<<SigNoise<<endl;
        while (!feof(UEList) && (count <= NumUsers))
        {
                fscanf(UEList,"%d", &timearrived);
                fscanf(UEList,"%d", &UID);
		fscanf(UEList,"%d", &RB);
                fscanf(UEList,"%f", &SigNoise);
                UE.time = timearrived;
                UE.UserID = UID;
		UE.ResourceBlock = RB - 1;
                UE.SINR = 10*(pow(10, SigNoise/10));
		UE.CQI = 0;
        UERegister.push_back(UE);
	count = UE.UserID;
        }
	return UERegister;

}

float UserEquipment::SINR_in_dB(UserEquipment &UE)
{
float i;
////do a calculation here
////and return the dB value.
	i = 10*(pow (10, UE.SINR/10));
	return i;
////
}

bool UserEquipment::getCandidateUE(int i, UserEquipment &UE)
{

if (UE.time==i)
return true;
else
return false;

}


void UserEquipment::getUEInfo(UserEquipment &UE)
{

cout<<"Time = "<<UE.time<<" User ID = "<<UE.UserID<<" Resource Block ID = "<<UE.ResourceBlock<<" SINR = "<<UE.SINR<<" DataRate = "<<UE.DataRate<<" Average Rate = "<<UE.AveDataRate<<" Sum Data Rate = "<<UE.SumDataRate<<endl;

}


UserEquipment UserEquipment::addCQI(UserEquipment &UE , int ChannelQuality)
{
UserEquipment tempUE;
	tempUE = UE;
	tempUE.CQI = ChannelQuality;
return tempUE;

}

vector<UserEquipment> UserEquipment::MaxRate(vector<UserEquipment> &UECandidateList)
{

vector<UserEquipment> tempQueue;
UserEquipment temp, testUE;
int RBcount = 0, i = 0, count = 0;
int tempQueueSize = 0;
int UECandidateListSize = 0;

float tempSINR = 0, MaxSINR = 0;

//i = UECandidateList.size(); 
UECandidateListSize = UECandidateList.size();

//while ((count<i) && (count<=24))
while ((count<UECandidateListSize) && (count<=24))
{
	temp=UECandidateList.at(count);
 	tempQueue.push_back(temp);
	count++;
}



tempQueueSize = tempQueue.size();
UECandidateListSize = UECandidateList.size();
//cout<<"TempQueue size = "<<tempQueueSize<<endl;
//cout<<"Cand Queue size = "<<UECandidateListSize<<endl;

//for (RBcount = 0; RBcount<tempQueue.size(); RBcount++)
//Maybe setup up a list of users in an array/vector.  Have the values in them set to boolean.
//as each user has a unique id, then i is the user id in the array.
//Then when an RB is allocated, can check the array, and get a true or false for allocation.
bool ResourceBlockTracker[100];
for (RBcount = 0; RBcount<tempQueueSize; RBcount++)
	{
	//for (i=0; i<UECandidateList.size(); i++)
	for (i=0; i<UECandidateListSize; i++)
		{
		temp = UECandidateList.at(i);
		if (temp.ResourceBlock 	== RBcount)
			{
			 	tempSINR=temp.SINR;
				if ((tempSINR > MaxSINR) && !ResourceBlockTracker[temp.UserID])
				{
					MaxSINR=tempSINR;
					tempQueue.at(RBcount) = temp;  
				}
			}
				


		}
		testUE=tempQueue.at(RBcount);
		ResourceBlockTracker[testUE.UserID] = true;
		MaxSINR = 0;

	}

return tempQueue;

}


int UserEquipment::GetUEquipmentUserID(UserEquipment &UE)
{

return UE.UserID;

}

float UserEquipment::GetSINR(UserEquipment &UE)
{

return UE.SINR;

}


UserEquipment UserEquipment::addRate(UserEquipment &UE , int DataRate)
{
UserEquipment tempUE;
	tempUE = UE;
	tempUE.DataRate = DataRate;
return tempUE;

}

UserEquipment UserEquipment::DecrementRate(UserEquipment &UE, int FrameSize)
{
UserEquipment newUE;
	newUE = UE;
	newUE.DataRate = (newUE.DataRate - FrameSize);
return newUE;
}

bool UserEquipment::CheckResourceAvailable(UserEquipment &UE, int FrameSize)
{

UserEquipment newUE;
if ((newUE.DataRate - FrameSize) > 0 )
		return true;
else 
		return false;
}

int UserEquipment::ShowRate(UserEquipment &UE)
{

return UE.DataRate;

}

int UserEquipment::ShowUserID(UserEquipment &UE)
{

return UE.UserID;

}

int UserEquipment::ShowRB(UserEquipment &UE)
{

return UE.ResourceBlock;

}

int UserEquipment::ShowTime(UserEquipment &UE)
{

return UE.time;

}

UserEquipment UserEquipment::UpdateAverageRate(UserEquipment &UE, int UEtime)
{
UserEquipment tempUE;
	tempUE = UE;
	tempUE.AveDataRate = (tempUE.SumDataRate)/(UEtime);
//cout<<"Average data rate = "<<tempUE.SumDataRate<<" Time = "<<tempUE.time<<" UserID = "<<tempUE.UserID<<endl;

return tempUE;
}

UserEquipment UserEquipment::UpdateSumRate(UserEquipment &UE, int DataRate)
{
UserEquipment tempUE;
	tempUE = UE;
	tempUE.SumDataRate = DataRate;
//cout<<"Sum data rate = "<<tempUE.SumDataRate<<" Time = "<<tempUE.time<<" UserID = "<<tempUE.UserID<<endl;

return tempUE;
}

vector<UserEquipment> UserEquipment::ProportionalFair(vector<UserEquipment> &UECandidateList)
{

vector<UserEquipment> tempQueue;
UserEquipment temp, testUE;
int RBcount = 0, i = 0, count = 0;
int tempQueueSize = 0;
int UECandidateListSize = 0;
bool ResourceBlockTracker[100];

//float tempSINR = 0, MaxSINR = 0;
float tempRate = 0, MRate = 0;

//i = UECandidateList.size(); 
UECandidateListSize = UECandidateList.size();

//while ((count<i) && (count<=24))
while ((count<UECandidateListSize) && (count<=24))
{
	temp=UECandidateList.at(count);
 	tempQueue.push_back(temp);
	count++;
}
tempQueueSize = tempQueue.size();
UECandidateListSize = UECandidateList.size();

for (RBcount = 0; RBcount<tempQueueSize; RBcount++)
	{
	for (i=0; i<UECandidateListSize; i++)
		{
		temp = UECandidateList.at(i);
		if (temp.ResourceBlock 	== RBcount)
			{
			 	tempRate=temp.AveDataRate;
				if ((tempRate > MRate) && !ResourceBlockTracker[temp.UserID])
				{
					MRate=tempRate;
					tempQueue.at(RBcount) = temp;  
				}
			}
		}
		testUE=tempQueue.at(RBcount);
		ResourceBlockTracker[testUE.UserID] = true;
		MRate = 0;
	}
return tempQueue;
}

void UserEquipment::SetRelayNode(UserEquipment &UE)
{

UE.RelayNode=true;

}

void UserEquipment::SeteNodeB(UserEquipment &UE)
{

UE.RelayNode=false;

}

void UserEquipment::ShowNodeStatus(UserEquipment &UE)
{

cout<<"Node status = "<<UE.RelayNode<<endl;

}
