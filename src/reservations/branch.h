//
// Created by solomspd on 03/12/2019.
//

#ifndef COMPUTER_ARCHITECTURE_PROJECT_2_BRANCH_H
#define COMPUTER_ARCHITECTURE_PROJECT_2_BRANCH_H


#include "station.h"

class branch : public station {
private:
    short address;
public:
    branch();
    ~branch();
    bool add_inst(short pc, instruction in_inst) override;
    short get_result() override;
};


#endif //COMPUTER_ARCHITECTURE_PROJECT_2_BRANCH_H
