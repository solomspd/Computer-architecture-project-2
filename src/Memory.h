#pragma once
#include "Registers.h"
#include "Registers.cpp"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
class Memory
{
public:
	Memory();
	~Memory();
	float getdata(int);
	void MemWrite(int, int);
	void initMem(int, float);
	void getfromfile(string);
private:
	float mem[128];
	int size;
	int count;
	char check;
	int location;
	float data;
	ifstream infile;
	Registers reg;
};

