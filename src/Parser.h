#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include<vector>
#include <deque>
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


	enum inst_type { LW, SW, ADD, SUB, ADDI, JMP, JALR, RET, BEQ, MUL, NAND, Garbage };
	struct instructionbase
	{
		inst_type type;
		short subtype;
		short rs1;
		short rs2;
		short rd;
		short imm;
	};
	instructionbase ParsedInstructions;
	std::vector<instructionbase>V_Instructions;
	Parser();
	Parser(string line);
	std::vector<instructionbase> Get_Instructions();
	string  get_inst();
	int  get_rs1();
	int get_rs2();
	int  get_rd();
	int get_imm();
	void print();
	ifstream infile;
	~Parser();
};

Parser::Parser()
{
	inst = Garbage;
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
std::vector<Parser::instructionbase> Parser::Get_Instructions()
{
	int pos, cursor, immediate_offset, location = 0, returnPosition;
	string check;
	cout << "Hello" << endl;
	while (!infile.eof())
	{
		getline(infile, LineInstruction);
		location++;
		immediate_offset = 0;
		if ((LineInstruction[0] == 'l') || (LineInstruction[0] == 's')) // LW OR SW
		{
			inst = LineInstruction.substr(0, 2);

			if (inst == "lw") // assume LW x1,0(x2);
			{
				ParsedInstructions.type = LW;
				LineInstruction.erase(0, 4);// remove lw from the line with the x in the register name
				pos = LineInstruction.find(",");
				ParsedInstructions.rd = stoi(LineInstruction.substr(0, pos));
				cout << "Rd: " << ParsedInstructions.rd;
				LineInstruction.erase(0, pos);// remove x1
				pos = LineInstruction.find("(");
				ParsedInstructions.imm = stoi(LineInstruction.substr(1, pos));
				cout << "\tImm: " << ParsedInstructions.imm;
				LineInstruction.erase(0, pos + 2);
				pos = LineInstruction.find(")");
				ParsedInstructions.rs1 = stoi(LineInstruction.substr(0, pos));
				cout << "\tRs1: " << ParsedInstructions.rs1 << endl;

			}
			else
				if (inst == "sw")
				{
					ParsedInstructions.type = SW;
					LineInstruction.erase(0, 4);// remove lw from the line with the x in the register name
					pos = LineInstruction.find(",");
					ParsedInstructions.rs2 = stoi(LineInstruction.substr(0, pos));
					cout << "Rs2: " << ParsedInstructions.rs2;
					LineInstruction.erase(0, pos);// remove x1
					pos = LineInstruction.find("(");
					ParsedInstructions.imm = stoi(LineInstruction.substr(1, pos));
					cout << "\tImm: " << ParsedInstructions.imm;
					LineInstruction.erase(0, pos + 2);
					pos = LineInstruction.find(")");
					ParsedInstructions.rs1 = stoi(LineInstruction.substr(0, pos));
					cout << "\tRs1: " << ParsedInstructions.rs1 << endl;
				}
				else
					if (inst == "su")
					{
						inst.erase(0, 5);
						ParsedInstructions.type = SUB;// remove sub and the x in the name of the register
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
					ParsedInstructions.type = BEQ;
					LineInstruction.erase(0, 5);
					pos = LineInstruction.find(',');
					rs1 = stoi(LineInstruction.substr(0, pos));
					ParsedInstructions.rs1 = rs1;
					LineInstruction.erase(0, pos + 2);// +2 to remove the extra space
					cout << "Rs1: " << rs1;

					pos = LineInstruction.find(',');
					rs2 = stoi(LineInstruction.substr(0, pos));
					ParsedInstructions.rs2 = rs2;
					LineInstruction.erase(0, pos + 1);// +2 to remove the extra space
					cout << "\tRs2: " << rs2;

					label = LineInstruction;
					//cout << label << endl;
					cursor = 4;
					returnPosition = infile.tellg();
					infile.clear();
					infile.seekg(ios_base::beg);
					while (!infile.eof())
					{
						getline(infile, check);
						immediate_offset++;
						//cout << check.substr(0, label.size() - 1) << "location: " << location << " imm1" << immediate_offset << endl;
						string temp = check.substr(0, label.size());
						if (temp == label)
						{
							imm = immediate_offset - location;
							ParsedInstructions.imm = imm;
							cout << "\tIMMpls: " << imm << endl;
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
						ParsedInstructions.type = JALR;
						LineInstruction.erase(0, 6);
						rs1 = stoi(LineInstruction);
						ParsedInstructions.rs1 = rs1;
						cout << "rs1: " << rs1 << endl;

					}
					else
						if (inst == "ret")
							ParsedInstructions.type = RET;

						else // j imm
						{
							ParsedInstructions.type = JMP;
							LineInstruction.erase(0, 2);
							label = LineInstruction;
							imm = stoi(LineInstruction);
							ParsedInstructions.imm = imm;
							cout << "IMM: " << imm << endl;
						}

				}
				else //R-instruction
					if (LineInstruction[0] == 'a')
					{
						inst = LineInstruction.substr(0, 4);
						if (inst == "addi")
						{
							LineInstruction.erase(0, 6);
							pos = LineInstruction.find(',');
							rs1 = stoi(LineInstruction.substr(0, pos));
							ParsedInstructions.rs1 = rs1;
							LineInstruction.erase(0, pos + 2);// +2 to remove the extra space
							cout << "Rs1: " << rs1;

							pos = LineInstruction.find(',');
							rs2 = stoi(LineInstruction.substr(0, pos));
							ParsedInstructions.rs2 = rs2;
							LineInstruction.erase(0, pos + 1);// +2 to remove the extra space
							cout << "\tRs2: " << rs2;

							imm = stoi(LineInstruction);
							ParsedInstructions.imm = imm;
							cout << "\tIMM: " << imm << endl;
						}

						else  // ADD
						{
							LineInstruction.erase(0, 5);
							pos = LineInstruction.find(',');
							rs1 = stoi(LineInstruction.substr(0, pos));
							ParsedInstructions.rs1 = rs1;
							LineInstruction.erase(0, pos + 2);// +2 to remove the extra space
							cout << "Rs1: " << rs1;

							pos = LineInstruction.find(',');
							rs2 = stoi(LineInstruction.substr(0, pos));
							ParsedInstructions.rs2 = rs2;
							LineInstruction.erase(0, pos + 2);// +2 to remove the extra space
							cout << "\tRs2: " << rs2;


							rd = stoi(LineInstruction);
							ParsedInstructions.rd = rd;
							cout << "\trd: " << rd << endl;
						}
					}
					else
						if (LineInstruction[0] == 'm')
						{
							inst = LineInstruction.substr(0, 3);
							if (inst == "mul")
							{
								LineInstruction.erase(0, 5);
								ParsedInstructions.type = MUL;
								pos = LineInstruction.find(',');
								rs1 = stoi(LineInstruction.substr(0, pos));
								ParsedInstructions.rs1 = rs1;
								LineInstruction.erase(0, pos + 2);// +2 to remove the extra space
								cout << "Rs1: " << rs1 << endl;

								pos = LineInstruction.find(',');
								rs2 = stoi(LineInstruction.substr(0, pos));
								ParsedInstructions.rs2 = rs2;
								LineInstruction.erase(0, pos + 2);// +2 to remove the extra space
								cout << "Rs2: " << rs2 << endl;

								rd = stoi(LineInstruction);
								ParsedInstructions.rd = rd;
								cout << "rd: " << rd << endl;

							}
						}
						else
							if (LineInstruction[0] == 'n')
							{
								inst = LineInstruction.substr(0, 4);
								if (inst == "nand")
								{
									LineInstruction.erase(0, 6);
									ParsedInstructions.type = NAND;

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
