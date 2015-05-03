// 
//Initial coding 7/7/2012.
//This is the UE class.
//It has a user ID, a time, and a SINR measurement.
//At present, the SINR measurement is read in from a file.
//But it could be generated in future releases. 
#include <iostream>
#include <vector>
#include "frame.h"
using namespace std;
//
//Need to add size as well as a data object, and maybe for the enQueue frame function
//
class UserEquipment
{
private:
	int time;
	int UserID;
	float SINR;
public:
	vector<UserEquipment> ReadInUE(FILE *UEList);
};
//
