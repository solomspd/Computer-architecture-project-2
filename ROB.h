class ROB
{
private:
	int ROB_index;
	char* Type;
	char* Dest;
	int value;
	bool ready; 
public:
	ROB();
	//ROB(int, char*, char*, int, bool);
	void setType(char*);
	void setDest(char*);
	void setValue(int, int);   //set value if the status is written, enum the state
	
//set the ready flag if the status is written and the instruction is the top of the queue
	void setReadinessStatus( std::queue<ROB>, int, char* instType, char* destination);
	// takes the instruction tag in the queue of the ROB
	bool getReadinessState();
	// takes the instruction tag in the queue of the ROB and returns the destination to be used in the registers table

};

// need an instruction base class that rob changes the status in