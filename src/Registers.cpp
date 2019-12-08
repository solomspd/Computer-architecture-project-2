#include "Registers.h"

Registers::Registers()
{
	size = 16;
	for (int i = 0; i < size; i++)
		reg[i] = 0;
}


Registers::~Registers()
{
}

void Registers::RegWrite(int data, int rd)
{
	reg[rd] = data;
}

float Registers::getReg(int imm)
{
	return reg[imm];
}

