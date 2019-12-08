#include "Memory.h"
#include "Registers.h"
#include "Registers.cpp"
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
	return mem[imm];
}

void Memory::MemWrite(int imm, int data)
{
	mem[imm] = data;
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
