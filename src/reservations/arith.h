//
// Created by solomspd on 03/12/2019.
//

#ifndef COMPUTER_ARCHITECTURE_PROJECT_2_ARITH_H
#define COMPUTER_ARCHITECTURE_PROJECT_2_ARITH_H

#include "station.h"

enum operation {add, sub};

class arith : public station {
private:
    operation op;
public:
    arith();
    ~arith();
    bool add_inst(instruction in_inst) override;
    short get_result() override;
};


#endif //COMPUTER_ARCHITECTURE_PROJECT_2_ARITH_H
