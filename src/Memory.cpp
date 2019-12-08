#include "Memory.h"
#include <iostream>
#include <string>
using namespace std;

Memory::Memory()
{
	size = 128;
	for(int i = 0; i < size; i++)
	mem[i] = 0;
	check = '\0';
}


Memory::~Memory()
{
}

float Memory::getdata(int imm)
{
	reg.getReg(imm);

}

void Memory::MemWrite(int imm, int data)
{
	reg.RegWrite(imm, data);
}

void Memory::initMem(int location, float data)
{
	mem[location] = data;
	cout << "\n Do you want to initailize another memory (Y) | (N)";
	cin >> check;
	check = tolower(check);
	if (check == 'y')
	{
		cout << "What is the memory location and data? ";
		cin >> location >> data;
		initMem(location, data);
	}
}
