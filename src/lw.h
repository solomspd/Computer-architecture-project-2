//
// Created by solomspd on 03/12/2019.
//

#ifndef COMPUTER_ARCHITECTURE_PROJECT_2_LW_H
#define COMPUTER_ARCHITECTURE_PROJECT_2_LW_H

#include "station.h"

class lw : public station {
private:
    short address;
    short *mem;
public:
    lw();

    lw(int c, short in_mem[]);

    ~lw();

    bool add_inst(instruction in_inst) override;

    short get_result() override;

    short get_addr() override;
};


#endif //COMPUTER_ARCHITECTURE_PROJECT_2_LW_H
