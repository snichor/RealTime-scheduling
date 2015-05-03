//intial code  13/07/2012.
//This will return the db value of SINR.
//Note that the function probably belongs in the user.h area.
//
//
#include <iostream>
#include <fstream>
#include <vector>
#ifndef CLI_H
#define CLI_H
using namespace std;
//
//
//
class Input
{
private:
//Not quite sure yet what goes here.
//Probably a vector with frames.
//
//So have vector<Frame> candidateFrames
//
//And this vector will change in size, depending on whether
//the frames have been transmitted, or reached maximum transmission count.
//One issue: Does the frame type need adjusting to account to transmissions?
//
	int NumUsers;
	int SimulationTime;
	int RB;
	int PacketScheduler;
public:
	
//Probably have a small vectore of frames here t transmit.
//So have some functions that are each a small vector of frames.
//Each function will be a specific packet scheduler.
//
	Input GetInput(int argc, char *argv[]);
	int GetNumberOfUsers(Input &InputCLI);
	int GetSimulationTime(Input &InputCLI);
	int GetPacketScheduler(Input &InputCLI);
};
#endif
//
//
