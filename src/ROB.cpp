#include "ROB.h"
#include"parser.h"
#include <deque>
ROB::ROB()
{
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
	if (InstState==written)
		value= InstResult;
	else 
		value=0;
}

void ROB::setReadinessStatus( std::deque<ROB>buffer, int InstState, int index)
{
	if (InstState==written /*&& buffer[index].Type==instType && buffer.front().Dest == destination*/)
		buffer[index].ready= 1;
	else 
		buffer[index].ready=0;
}

	bool ROB::getReadinessState()
{
	return ready;
}