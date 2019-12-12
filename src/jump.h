//
// Created by solomspd on 03/12/2019.
//

#ifndef COMPUTER_ARCHITECTURE_PROJECT_2_JUMP_H
#define COMPUTER_ARCHITECTURE_PROJECT_2_JUMP_H


#include "station.h"


class jump : public station {
private:
    short address;
    short *pc;
    j_type op;
public:
    jump();

    jump(int c, short *pc);

    ~jump();

    bool add_inst(instruction in_inst) override;

    short get_result() override;
};


#endif //COMPUTER_ARCHITECTURE_PROJECT_2_JUMP_H
