// on using classes.  11/6/2012.
#include <iostream>
#include <vector>
#include <cmath>
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include "user.h"
#include "frame.h"
#include "PacketScheduler.h"
#include "CLI.h"
using namespace std;
//
//function declarations
//
//


Input Input::GetInput(int argc, char *argv[])
{
Input InputValues;
//
//Use the getopt function here
//Maybe this does not need to return a value?
//Or maybe just return an input var.
 int opt, SimTime, NumberOfUsers, PScheduler;
// char argument [256];

   SimTime = 0;
   NumberOfUsers = 0;
   PScheduler = 0;
    	while ((opt = getopt(argc, argv, "t:n:s:")) != -1) 
	{
				//cout<<"argc  = "<<argc<<" argv = %s "<<argv[optind]<<endl;
        	switch (opt) 
		{
        		case 't':
				cout<<"1. Time  = "<<SimTime<<endl;
            			SimTime = atoi(optarg);
				InputValues.SimulationTime = SimTime;	
				cout<<"2. Time  = "<<SimTime<<endl;
            			break;
			case 'n':
				cout<<"1. Users  = "<<NumberOfUsers<<endl;
            			NumberOfUsers = atoi(optarg);
				InputValues.NumUsers = NumberOfUsers;
				cout<<"2. Users  = "<<NumberOfUsers<<endl;
				break;
			case 's':
				PScheduler = atoi(optarg);
				InputValues.PacketScheduler = PScheduler;
				break;
				
        		default: /* '?' */
            			cout<<"Usage -t time -n number of users -s Scheduler"<<endl;
            			exit(EXIT_FAILURE);
       		}
    	}
	cout<<"NumUsers = "<<InputValues.NumUsers<<" Time = "<<InputValues.SimulationTime<<endl;


return InputValues;
}


int Input::GetNumberOfUsers(Input &InputCLI)
{

return InputCLI.NumUsers;

}


int Input::GetSimulationTime(Input &InputCLI)
{

return InputCLI.SimulationTime;

}

int Input::GetPacketScheduler(Input &InputCLI)
{

return InputCLI.PacketScheduler;

}
