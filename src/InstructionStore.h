#include <vector>
#include"ROB.h"


class InstructionStore
{
private:
	char* Type;
	char* Dest;
	enum state { None,issued, executed, written, commited };
	enum latencies { load = 3, store = 3, jump = 1, add = 2, sub = 2, addi = 2, nand = 1, mul = 10 };
	struct instructionVector
	{
		char* type;
		char* dest;
		state state1;
	};


public:
	std::vector<instructionVector> instructions;
	InstructionStore();
	// will take the vector of instructions' type generated somewhere discuss with them
	std::vector<instructionVector>InstructionBase(std::vector<char*>, std::vector<char*>, std::vector<state>);

	void updateIssue_ExecState(std::vector<instructionVector>, int, Session s1, int rs_index);
	void updateExec_WriteState(std::vector<instructionVector>, int , Session s1, int rs_index);
	void updateWrite_CommitState(std::vector<instructionVector>, ROB& , int index);

	void ForwardInstruction(ROB &entry, ReservationStation &rs, std::vector<instructionVector> instructions, int index, int PC);
	void LoadWrite(ROB& );
	void StoreWrite(ROB &);
	void RInst(ReservationStation&, ROB&);
	void PCUpdate(ROB&, int PC);

};
