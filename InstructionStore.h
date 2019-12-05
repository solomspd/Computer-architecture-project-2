#include <vector>
class InstructionStore
{
private:
	char* Type;
	char* Dest;
	enum state { issued, executed, written, commited };
	enum latencies { load=3, store=3, jump=1, add=2, sub=2, addi=2, nand=1, mul=10 };
	struct instructionVector
	{
		char* type;
		char* dest;
		state state1;
	};

public:
	InstructionStore();
// will take the vector of instructions' type generated somewhere discuss with them
	std::vector<instructionVector>InstructionBase(std::vector<char*>, std::vector<char*>, std::vector<state>);
	
	void updateState(std::vector<instructionVector>);
}; 
