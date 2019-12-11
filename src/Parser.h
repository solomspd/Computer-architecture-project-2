#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include<vector>
#include <deque>
#include "reservations/station.h"
//#include "Hash.hpp"
using namespace std;
/****************************************************************************************/
/*                           Parser Prototype                                */
/****************************************************************************************/
class Parser
{
private:
	string inst;
	string LineInstruction;
	int rs1;
	int rs2;
	int rd;
	int imm;
	int subtype;
	string label;



public:
	// subtype arth : 0= add , 1=sub, 2=addi
	// subtype jump : 0=Jmp,  1=JALR , 2= RET
	// subtype branch: 0= Beq

	instruction ParsedInstructions;
	std::vector<instruction>V_Instructions;
	Parser();
	Parser(string line);
	std::vector<instruction> Get_Instructions();
	string  get_inst();
	int  get_rs1();
	int get_rs2();
	int  get_rd();
	int get_imm();
	ifstream infile;
	~Parser();
};

Parser::Parser()
{
	subtype = -1;
	rs1 = -1;
	rs2 = -1;
	rd = -1;
	imm = -1;
}


Parser::Parser(string line)//:Parser()
{// contructor with parameter to read from file

	infile.open(line);
}
std::vector<instruction> Parser::Get_Instructions()
{
	int pos, cursor, immediate_offset, location = 0, returnPosition;
	string check;
	while (!infile.eof())
	{
		getline(infile, LineInstruction);
		location++;
		immediate_offset = 0;
		if ((LineInstruction[0] == 'l') || (LineInstruction[0] == 's')) // LW OR SW
		{
			inst = LineInstruction.substr(0, 2);

			if (inst == "lw") // example lw x1,0(x2);
			{
				ParsedInstructions.inst_t = l;
				LineInstruction.erase(0, 4);// remove lw from the line with the x in the register name
				pos = LineInstruction.find(",");
				ParsedInstructions.rd = stoi(LineInstruction.substr(0, pos));
				LineInstruction.erase(0, pos);// remove x1
				pos = LineInstruction.find("(");
				ParsedInstructions.imm = stoi(LineInstruction.substr(1, pos));
				LineInstruction.erase(0, pos + 2);
				pos = LineInstruction.find(")");
				ParsedInstructions.rs1 = stoi(LineInstruction.substr(0, pos));
			

			}
			else
				if (inst == "sw")
				{
					ParsedInstructions.inst_t = s;
					LineInstruction.erase(0, 4);// remove lw from the line with the x in the register name
					pos = LineInstruction.find(",");
					ParsedInstructions.rs2 = stoi(LineInstruction.substr(0, pos));
					LineInstruction.erase(0, pos);// remove x1
					pos = LineInstruction.find("(");
					ParsedInstructions.imm = stoi(LineInstruction.substr(1, pos));
					LineInstruction.erase(0, pos + 2);
					pos = LineInstruction.find(")");
					ParsedInstructions.rs1 = stoi(LineInstruction.substr(0, pos));
				}
				else
					if (inst == "su")
					{

						inst.erase(0, 5);
						ParsedInstructions.inst_t = a;
						ParsedInstructions.sub_type = 2;
						pos = LineInstruction.find(",");
						ParsedInstructions.rs1 = stoi(LineInstruction.substr(0, pos));
						LineInstruction.erase(0, pos + 2);
						pos = LineInstruction.find(",");
						ParsedInstructions.rs2 = stoi(LineInstruction.substr(0, pos));
						LineInstruction.erase(0, pos + 2);
						imm = stoi(LineInstruction);
					}

		}

		else // BEQ INSTRUCTION
			if ((LineInstruction[0]) == 'b')
			{
				inst = LineInstruction.substr(0, 3);
				if (inst == "beq")
				{
					ParsedInstructions.inst_t = b;
					LineInstruction.erase(0, 5);
					pos = LineInstruction.find(',');
					ParsedInstructions.rs1 = stoi(LineInstruction.substr(0, pos));
					LineInstruction.erase(0, pos + 2);// +2 to remove the extra space

					pos = LineInstruction.find(',');
					ParsedInstructions.rs2 = stoi(LineInstruction.substr(0, pos));
					LineInstruction.erase(0, pos + 1);// +2 to remove the extra space

					label = LineInstruction;
					returnPosition = infile.tellg();
					infile.clear();
					infile.seekg(ios_base::beg);
					while (!infile.eof())
					{
						getline(infile, check);
						immediate_offset++;
						string temp = check.substr(0, label.size());
						if (temp == label)
						{
							ParsedInstructions.imm = immediate_offset - location;
							infile.seekg(ios_base::beg);
							infile.seekg(returnPosition);
							break;
						}
					}
				}
			}

			else // J INSTRUCTION
				if ((LineInstruction[0] == 'j') || (LineInstruction[0] == 'l') || (LineInstruction[0] == 'r'))
				{
					inst = LineInstruction.substr(0, 3);
					if (inst == "jal") // JALR
					{
						ParsedInstructions.inst_t = j;
						ParsedInstructions.sub_type = 1;
						LineInstruction.erase(0, 6);
						rs1 = stoi(LineInstruction);
						ParsedInstructions.rs1 = rs1;

					}
					else
						if (inst == "ret")
						{
							ParsedInstructions.inst_t = j;
							ParsedInstructions.sub_type = 2;
						}
						else // j imm
						{
							ParsedInstructions.inst_t = j;
							ParsedInstructions.sub_type = 0;
							LineInstruction.erase(0, 2);
							label = LineInstruction;
							ParsedInstructions.imm = stoi(LineInstruction);
						}

				}
				else //Arithmatic
					if (LineInstruction[0] == 'a')
					{
						inst = LineInstruction.substr(0, 4);

						if (inst == "addi")
						{
							ParsedInstructions.inst_t = a;
							ParsedInstructions.sub_type = 1;
							LineInstruction.erase(0, 6);
							pos = LineInstruction.find(',');
							rs1 = stoi(LineInstruction.substr(0, pos));
							ParsedInstructions.rs1 = rs1;
							LineInstruction.erase(0, pos + 2);// +2 to remove the extra space

							pos = LineInstruction.find(',');
							rs2 = stoi(LineInstruction.substr(0, pos));
							ParsedInstructions.rs2 = rs2;
							LineInstruction.erase(0, pos + 1);// +2 to remove the extra space

							imm = stoi(LineInstruction);
							ParsedInstructions.imm = imm;
						}

						else  // ADD
						{
							ParsedInstructions.inst_t = a;
							ParsedInstructions.sub_type = 0;
							LineInstruction.erase(0, 5);
							pos = LineInstruction.find(',');
							rs1 = stoi(LineInstruction.substr(0, pos));
							ParsedInstructions.rs1 = rs1;
							LineInstruction.erase(0, pos + 2);// +2 to remove the extra space

							pos = LineInstruction.find(',');
							rs2 = stoi(LineInstruction.substr(0, pos));
							ParsedInstructions.rs2 = rs2;
							LineInstruction.erase(0, pos + 2);// +2 to remove the extra space


							rd = stoi(LineInstruction);
							ParsedInstructions.rd = rd;
						}
					}
					else
						if (LineInstruction[0] == 'm')
						{
							inst = LineInstruction.substr(0, 3);
							if (inst == "mul")
							{
								LineInstruction.erase(0, 5);
								ParsedInstructions.inst_t = m;
								pos = LineInstruction.find(',');
								rs1 = stoi(LineInstruction.substr(0, pos));
								ParsedInstructions.rs1 = rs1;
								LineInstruction.erase(0, pos + 2);// +2 to remove the extra space

								pos = LineInstruction.find(',');
								rs2 = stoi(LineInstruction.substr(0, pos));
								ParsedInstructions.rs2 = rs2;
								LineInstruction.erase(0, pos + 2);// +2 to remove the extra space

								rd = stoi(LineInstruction);
								ParsedInstructions.rd = rd;

							}
						}
						else
							if (LineInstruction[0] == 'n')
							{
								inst = LineInstruction.substr(0, 4);
								
								if (inst == "nand")
								{
									LineInstruction.erase(0, 6);
									ParsedInstructions.inst_t = n;

									pos = LineInstruction.find(',');
									ParsedInstructions.rs1 = stoi(LineInstruction.substr(0, pos));
									LineInstruction.erase(0, pos + 2);

									pos = LineInstruction.find(',');
									ParsedInstructions.rs2 = stoi(LineInstruction.substr(0, pos));
									LineInstruction.erase(0, pos + 2);

									ParsedInstructions.rd = stoi(LineInstruction);
								}
							}
	}
	V_Instructions.push_back(ParsedInstructions);
	infile.close();
	return V_Instructions;
}
string Parser::get_inst() 
{// ip getter
	return inst;
}
int Parser::get_rs1() { return rs1; }
int Parser::get_rs2() { return rs2; }
int Parser::get_rd() { return rd; }
int Parser::get_imm() { return imm; }
Parser:: ~Parser() { infile.close(); }
