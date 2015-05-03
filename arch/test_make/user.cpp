// on using classes.  11/6/2012.
#include <iostream>
#include <vector>
#include "user.h"
#include "frame.h"
using namespace std;
//
//function declarations
//
//

vector<UserEquipment> UserEquipment::ReadInUE(FILE *UEList)
{
UserEquipment UE;
vector<UserEquipment> UERegister;
int UID = 0, timearrived = 0;
float SigNoise;
	cout<<"SINR = "<<SigNoise<<endl;
	UEList = fopen("UE_List.txt","r");
        while (!feof(UEList))
        {
                fscanf(UEList,"%d", &timearrived);
                fscanf(UEList,"%d", &UID);
                fscanf(UEList,"%f", &SigNoise);
                UE.time = timearrived;
                UE.UserID = UID;
                UE.SINR = SigNoise;
	cout<<"time arrived = "<<UE.time<<" UserID = "<<UE.UserID<<" SINR = "<<UE.SINR<<endl;
        UERegister.push_back(UE);
        }
	fclose(UEList);
	return UERegister;

}

