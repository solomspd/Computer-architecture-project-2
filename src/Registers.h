#pragma once
class Registers
{
public:
	Registers();
	~Registers();
	void RegWrite(int, int);
	float getReg(int);
private:
	float reg[16];
	int size;

};

