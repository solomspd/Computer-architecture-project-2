#include "InstructionStore.h"
#include"parser.h"
#include "ROB.h"
#include <deque>

InstructionStore::InstructionStore()
{
	Type = "";
	Dest = "";
}
// instType will be received from the parser class
std::vector<InstructionStore::instructionVector>InstructionStore::InstructionBase(std::vector<char*> Types, std::vector<char*>destinations, std::vector<state>states)
{
	for (int i = 0; i < Types.size(); i++)
	{
		instructions[i].type = Types[i];
		instructions[i].dest = destinations[i];
		instructions[i].state1 = None;
	}
	return instructions;
}

void InstructionStore::ForwardInstruction(ROB &entry, ReservationStation &rs, std::vector<instructionVector> instructions, int index, int PC)
{
	if (instructions[index].state1 == commited) {
		if (instructions[index].type == "LW")
		{
			LoadWrite(entry);
		}

		if (instructions[index].type == "SW")
		{
			StoreWrite(entry);
		}

		if (instructions[index].type == "ADD"|| instructions[index].type == "SUB"|| instructions[index].type == "ADDI")
		{
			RInst(rs,entry);
		}

		if (instructions[index].type == "BEQ" || instructions[index].type == "JMP" )
		{
			PCUpdate(entry, PC);
		}


	}
}

void InstructionStore::updateIssue_ExecState(std::vector<instructionVector> instructions, int index, Session s1, int rs_index)
{
	// just check REG/ROB table and update instructions[index].state1 accordingly 
}




void InstructionStore::updateExec_WriteState(std::vector<instructionVector> instructions, int index, Session s1, int rs_index )
{
	if ((instructions[index].type == "LD"|| instructions[index].type == "SW") && s1[rs_index].Qj==0 && instructions[index].state1==executed)
	{
		// after 3 clock cycles, change the state to written
		instructions[index].state1 == written;
	}

	if ((instructions[index].type == "ADD" || instructions[index].type == "SUB"|| instructions[index].type == "ADDI") && s1[rs_index].Qj == 0 && s1[rs_index].Qk == 0 && instructions[index].state1 == executed)
	{
		// after 2 clock cycles, change the state to written
		instructions[index].state1 == written;
	}
	
	if ((instructions[index].type == "JMP" || instructions[index].type == "JALR" ||
	instructions[index].type == "RET"|| instructions[index].type == "BEQ"|| instructions[index].type == "NAND")
		&& s1[rs_index].Qj == 0 && s1[rs_index].Qk == 0 && instructions[index].state1 == executed)
	{
		// after 1 clock cycles, change the state to written
		instructions[index].state1 == written;
	}

	if (instructions[index].type == "MULD" && s1[rs_index].Qj == 0 && s1[rs_index].Qk == 0 && instructions[index].state1 == executed)
	{
		// after 10 clock cycles, change the state to written
		instructions[index].state1 == written;
	}

}



void InstructionStore::updateWrite_CommitState(std::vector<instructionVector>instructions, std::deque<ROB>entry, int index)
{
	if (entry.front().Dest == instructions[index].dest && entry.front().Type == instructions[index].type)
	{
		if (entry[index].ready == 1)
		{
			instructions[index].state1 == commited;
		}
	}
}



void InstructionStore::LoadWrite(ROB &entry)
{
		// get entry[index].value from the memory class M[entry[index].value] and write it to the entry[index].dest in the register file ; REG[entry[index].dest]
}


void InstructionStore::StoreWrite(ROB &entry)
{
		// get the value of entry[index].dest from the register class REG[entry[index].dest]and write it in entry[index].value in the memory class M[entry[index].value] 	
}

void InstructionStore:: RInst(ReservationStation&rs, ROB &entry)
{

	// get the value of Vj and Vk from the ReservationStations and write the requied in the register class REG[entry[index].dest]

	switch (entry.Type)
		case "ADD":
		case "SUB":
		case "ADDI":
}


int InstructionStore::PCUpdate(ROB &entry, int PC)
{
	// update pc to jump entry.value+PC
	return PC;
}