#include <iostream>
#include <vector>
#include <cmath>
#include "user.h"
#include "frame.h"
#include "eNodeB.h"
using namespace std;
//
//function declarations
//
//

int eNodeB::GetCellID(int getsomeint, eNodeB RFNode)
{

return RFNode.CellID;

}

bool eNodeB::IsRelayNode(eNodeB RFNode)
{

return RFNode.Relay;

}


