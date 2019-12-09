#include<vector>
#include<utility>

enum state { None, issued, executed, written, commited };

class ROB
{
private:
	int ROB_index;
	int Type;
	int Dest;
	int value;
	bool ready;
	std::vector<std::pair<short*, int>>tracking;
	//	std::deque<ROB> rob;
public:
	ROB();
	//ROB(int, char*, char*, int, bool);
	void setType(int type_enum);
	void setDest(int);
	void setValue(int, int);   //set value if the status is written, enum the state
	void reserve(short*, int, std::vector<ROB>);
	//void setIndex(int);
	int getIndex(std::vector<ROB>);
	//	void FlushForBranch(bool misprediction_flag);
	//set the ready flag if the status is written and the instruction is the top of the queue
	void setReadinessStatus(std::vector<ROB>, int, int);
	// takes the instruction tag in the queue of the ROB
	bool getReadinessState();
	// takes the instruction tag in the queue of the ROB and returns the destination to be used in the registers table

};

// need an instruction base class that rob changes the status in