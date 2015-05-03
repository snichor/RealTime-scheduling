//Program to set up the UE queues.  13/6/2012.
#include <iostream>
#include <vector>
#include "frame.h"	
#include "user.h"	
using namespace std;

//
//
//main program
//
//
int main ()
{
FILE *UEFile;
Frame temp;
UserEquipment UE;
  int i = 10;
  int j = 84;
  int k = 0;
  vector<UserEquipment> UEList;
  UEList = UE.ReadInUE(UEFile);
      cout<<"i = "<<i<<endl;	
       return 0;
}
