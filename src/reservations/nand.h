//
// Created by solomspd on 03/12/2019.
//

#ifndef COMPUTER_ARCHITECTURE_PROJECT_2_NAND_H
#define COMPUTER_ARCHITECTURE_PROJECT_2_NAND_H


#include "station.h"

class nand : private station{
private:

public:
    nand();
    ~nand();
    bool add_inst(short rs1, short rs2, short rd);
};


#endif //COMPUTER_ARCHITECTURE_PROJECT_2_NAND_H
