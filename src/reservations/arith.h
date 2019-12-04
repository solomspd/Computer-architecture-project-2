//
// Created by solomspd on 03/12/2019.
//

#ifndef COMPUTER_ARCHITECTURE_PROJECT_2_ARITH_H
#define COMPUTER_ARCHITECTURE_PROJECT_2_ARITH_H

#include "station.h"

enum operation {add, sub, addi};

class arith : private station {
private:
    operation op;
public:
    arith();
    ~arith();
    bool add_inst(short rs1, short rs2, short rd)
};


#endif //COMPUTER_ARCHITECTURE_PROJECT_2_ARITH_H
