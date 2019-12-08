#pragma once
class Memory
{
public:
	Memory();
	~Memory();
	float getdata(int);
	void MemWrite(int, int);
	void initMem(int, float);
private:
	float mem[128];
	int size;
	char check;
	int location;
	float data;
};

