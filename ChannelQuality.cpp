// on using classes.  11/6/2012.
#include <iostream>
#include <vector>
#include <cmath>
#include "user.h"
#include "frame.h"
#include "ChannelQuality.h"
using namespace std;
//
//function declarations
//
//
/*vector<ResourceBlock> ResourceBlock::GetRBsForTX(int i, vector<ResourceBlock> &RB)
{
vector<ResourceBlock> temp;
temp = RB;
cout<<"Got here"<<endl;
return temp;
}A*/

vector<ChannelQuality> ChannelQuality::ReadInLimits(FILE *LimitFile)
{
vector<ChannelQuality> CQIqueue;
ChannelQuality CQIndex;
float lower, upper;
int rate;
 while (!feof(LimitFile))
        {
                fscanf(LimitFile,"%f",&lower);
                fscanf(LimitFile,"%f",&upper);
                fscanf(LimitFile,"%d",&rate);
                CQIndex.LowerLimit = lower;
                CQIndex.UpperLimit = upper;
                CQIndex.DataRate = rate;
         CQIqueue.push_back(CQIndex);
	}


 return CQIqueue;

}



float ChannelQuality::FindRate(float SINR, vector<ChannelQuality> CQIDB)
{
int count = 0;
ChannelQuality tempCQI;
float DataRate;
int QueueSize;

QueueSize = CQIDB.size();

for (count = 0; count<QueueSize; count++)
	{
		tempCQI=CQIDB.at(count);
		if ( (SINR > tempCQI.LowerLimit) && (SINR < tempCQI.UpperLimit) )
			DataRate = tempCQI.DataRate;
	}
	return DataRate;
}


int ChannelQuality::FindCQI(float SINR, vector<ChannelQuality> CQIDB)
{
int count = 0;
ChannelQuality tempCQI;
//float DataRate;
int CQI = 0;
int QueueSize;

QueueSize = CQIDB.size();

for (count = 0; count<QueueSize; count++)
	{
		tempCQI=CQIDB.at(count);
		if ( (SINR > tempCQI.LowerLimit) && (SINR < tempCQI.UpperLimit) )
			CQI = count;	
			//DataRate = tempCQI.DataRate;
	}
	return CQI;
}

