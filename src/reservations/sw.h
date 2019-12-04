//
// Created by solomspd on 03/12/2019.
//

#ifndef COMPUTER_ARCHITECTURE_PROJECT_2_SW_H
#define COMPUTER_ARCHITECTURE_PROJECT_2_SW_H


#include "station.h"

class sw : private station {
private:
    short address;
public:
    sw();
    ~sw();
    bool add_inst(short rs1, short rs2, short imm);
};


#endif //COMPUTER_ARCHITECTURE_PROJECT_2_SW_H
