#include "ROB.h"
#include"parser.h"
#include <deque>
ROB::ROB()
{
	 ROB_index =0;
	 Type=0;
	 Dest=0;
	 value=0;
	 ready=0; 
}
// instType will be received from the parser class
void ROB::setType(int type_enum)
{
	Type= type_enum;
}
// destinationRegister will be received from the parser class

void ROB::setDest(int destinationRegister)
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

void ROB::setReadinessStatus( std::vector<ROB>buffer, int InstState, int index)
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


int ROB::getIndex(std:: vector<ROB>rob )
{
	return rob.back().ROB_index;
}

void ROB::reserve(short*result, int inst_no, std:: vector<ROB> rob  )
{
	if (result==nullptr)
	{
		std::pair <short*, int >temp;
		temp.first=result;
		temp.second= inst_no;
		tracking.push_back(temp);	
	//	if (result==Yes|| result==0)
		for (int i=0; i<tracking.size(); i++) 
		{
			if (tracking[i].second==!nullptr)
			{
				rob[i].value= *(tracking[i].first);
				//tracking.pop_back();
				tracking.erase(tracking.begin() + i);
				break;	
			}
		}
	}
	//else
	//{
	//	rob[inst_no].value= *result;
	//}
}

void ROB:: advance_cycle(short*result, int inst_no, std:: vector<ROB> rob)
{
	for (int i=0; i<tracking.size(); i++) 
	{
		if (tracking[i].second==!nullptr)
		{
			rob[i].value= *(tracking[i].first);
			//tracking.pop_back();
			tracking.erase(tracking.begin() + i);
			break;	
		}
	}
}
// to be added to tomasulo
//std::deque<ROB> rob;
//int rob_size;
//int count=0;
//ROB instruction;
//instruction.index=count;
//instruction.Type="";
//instruction.Dest="";
//instruction.value;
//instruction.ready=false; 

//void pushToROB(ROB instruction)
//{
//	if (count<rob_size)
//	{	rob.push_back(intstruction);
//		count++;
//	}
//	else 
//	issue_flag = false;
//}
//
//
//void PopFromROB()
//{
//		if (rob.front().ready==Yes)
//		{
//		//  call execute function, don't know in which class 
//		rob.erase(rob.begin());
//		count--;
//		issue_flag=true
//		}
//}
//
//if (issue_flag && funcUnitFlag )
//while (dualIssue < 2)
//{
//	the whole code
//	dualIssue++;
//}

//FlushForBranch(bool Jump_flag, int inst_no)
//{
//	if (Jump_flag)
//		rob.erase(rob.begin(), rob.begin() +inst_no );
//
//}
