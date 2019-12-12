//
// Created by solomspd on 03/12/2019.
//

#ifndef COMPUTER_ARCHITECTURE_PROJECT_2_MULT_H
#define COMPUTER_ARCHITECTURE_PROJECT_2_MULT_H


#include "station.h"

class mult : public station {
private:

public:
    mult(int c);

    ~mult();

    bool add_inst(instruction in_inst);

    short get_result() override;
};


#endif //COMPUTER_ARCHITECTURE_PROJECT_2_MULT_H
