#include "ROB.h"
#include"parser.h"
#include<queue>
ROB::ROB()
{
	 ROB_index=0;
	 Type="";
	 Dest="";
	 value=0;
	 ready=0; 
}
// instType will be received from the parser class
void ROB::setType(char* instType)
{
	Type= instType;
}
// destinationRegister will be received from the parser class

void ROB::setDest(char* destinationRegister)
{
	Dest= destinationRegister;
}
// this value will be retreived from the memory module
void ROB::setValue(int InstResult, int InstState)
{
	if (InstState==1)
		value= InstResult;
	else 
		value=0;
}

void ROB::setReadinessStatus( std::queue<ROB>buffer, int InstState, char* instType, char* destination)
{
	if (InstState==2 && buffer.front().Type==instType && buffer.front().Dest == destination)
		ready= 1;
	else 
		ready=0;
}

	bool ROB::getReadinessState()
{
	return ready;
}