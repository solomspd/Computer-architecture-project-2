//
// Created by solomspd on 03/12/2019.
//

#ifndef COMPUTER_ARCHITECTURE_PROJECT_2_LW_H
#define COMPUTER_ARCHITECTURE_PROJECT_2_LW_H

#include "station.h"

class lw : public station{
private:
    short address;
public:
    lw();
    ~lw();
    bool add_inst(instruction in_inst) override;
    short get_result() override;
};


#endif //COMPUTER_ARCHITECTURE_PROJECT_2_LW_H
