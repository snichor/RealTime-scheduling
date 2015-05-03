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
//
//5/10/2012
//Probably will add the scheduler functions in here and remove them from the
//user.h files.  This may mean adding in the objects to use here as well.
//
#include <iostream>
#include <vector>
//#include "frame.h"
#ifndef ENODEB_H
#define ENODEB_H
using namespace std;
//
//Need to add size as well as a data object, and maybe for the enQueue frame function
//
class eNodeB
{
private:
//Below two put in 30/9/2012.  Currently seeing if these test out ok.
	int CellID;
	bool Relay;
	vector<int> UERegister;
	//int UserEqID;
public:
	int GetCellID(int someint, eNodeB RFNode);
	bool IsRelayNode(eNodeB RFNode);

};
	
#endif
