//
// Created by solomspd on 03/12/2019.
//

#ifndef COMPUTER_ARCHITECTURE_PROJECT_2_LW_H
#define COMPUTER_ARCHITECTURE_PROJECT_2_LW_H

#include "station.h"

class lw : private station{
private:
    short address;
public:
    lw();
    ~lw();
    bool add_inst(short rs1, short rd, short imm)
};


#endif //COMPUTER_ARCHITECTURE_PROJECT_2_LW_H