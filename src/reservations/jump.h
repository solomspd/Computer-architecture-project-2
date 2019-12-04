//
// Created by solomspd on 03/12/2019.
//

#ifndef COMPUTER_ARCHITECTURE_PROJECT_2_JUMP_H
#define COMPUTER_ARCHITECTURE_PROJECT_2_JUMP_H


#include "station.h"

class jump : private station {
private:
    short address;
public:
    jump();
    ~jump();
    bool add_inst(short pc_in, short imm);
};


#endif //COMPUTER_ARCHITECTURE_PROJECT_2_JUMP_H
