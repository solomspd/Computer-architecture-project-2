//
// Created by solomspd on 03/12/2019.
//

#ifndef COMPUTER_ARCHITECTURE_PROJECT_2_MULT_H
#define COMPUTER_ARCHITECTURE_PROJECT_2_MULT_H


#include "station.h"

class mult : private station {
private:

public:
    mult();
    ~mult();
    bool add_inst(short rs1, short rs2, short rd);

};


#endif //COMPUTER_ARCHITECTURE_PROJECT_2_MULT_H