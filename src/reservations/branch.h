//
// Created by solomspd on 03/12/2019.
//

#ifndef COMPUTER_ARCHITECTURE_PROJECT_2_BRANCH_H
#define COMPUTER_ARCHITECTURE_PROJECT_2_BRANCH_H


#include "station.h"

class branch : private station {
private:
    short address;
public:
    branch();
    ~branch();
    bool add_inst(short pc, short rs1, short rs2, short imm);
};


#endif //COMPUTER_ARCHITECTURE_PROJECT_2_BRANCH_H