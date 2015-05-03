// 
//Initial coding 7/7/2012.
//Update 13/7/2012.
//Add in will be a function that can calculate the SINR for the given value.
//Another function can work out the CQI.
//I am not sure if we just need to have this do ne once; the scheduler
//can work out which packet to schedule
//
//Below is the UE class.
//It has a user ID, a time, and a SINR measurement.
//At present, the SINR measurement is read in from a file.
//But it could be generated in future releases. 
#include <iostream>
#include <vector>
//#include "frame.h"
#ifndef USER_H
#define USER_H
using namespace std;
//
//Need to add size as well as a data object, and maybe for the enQueue frame function
//
class UserEquipment
{
private:
	int time;
	int UserID;
	int ResourceBlock;
	float SINR;
	int CQI;
	int DataRate;	
	int SumDataRate;
	float AveDataRate;
//Below two put in 30/9/2012.  Currently seeing if these test out ok.
	int CellID;
	bool RelayNode;
	int RelayID;
public:
	vector<UserEquipment> ReadInUE(FILE *UEList, int NumUsers);
	float SINR_in_dB(UserEquipment &UE);
	bool getCandidateUE(int i, UserEquipment &UE);
	void getUEInfo(UserEquipment &UE);
	//int getCQI(UserEquipment &UE);
	UserEquipment addCQI(UserEquipment &UE, int ChannelQuality);
	UserEquipment addRate(UserEquipment &UE, int Rate);
	vector<UserEquipment> MaxRate(vector<UserEquipment> &UECandidateList);
	vector<UserEquipment> ProportionalFair(vector<UserEquipment> &UECandidateList);
	int GetUEquipmentUserID(UserEquipment &UE);
	float GetSINR(UserEquipment &UE);
	UserEquipment DecrementRate(UserEquipment &UE, int FrameSize);
	bool CheckResourceAvailable(UserEquipment &UE, int FrameSize);
	int ShowRate(UserEquipment &UE);
	int ShowUserID(UserEquipment &UE);
	int ShowRB(UserEquipment &UE);
	int ShowTime(UserEquipment &UE);
	UserEquipment UpdateAverageRate(UserEquipment &UE, int UEtime);
	UserEquipment UpdateSumRate(UserEquipment &UE, int Rate);
	void SetRelayNode(UserEquipment &UE);
	void SeteNodeB(UserEquipment &UE);
	void ShowNodeStatus(UserEquipment &UE);
	//void DecrementDataRate(UserEquipment &UE);
};
	
#endif
