//
// Created by solomspd on 03/12/2019.
//

#ifndef COMPUTER_ARCHITECTURE_PROJECT_2_JUMP_H
#define COMPUTER_ARCHITECTURE_PROJECT_2_JUMP_H


#include "station.h"

enum type {jmp, jalr, ret};

class jump : public station {
private:
    short address;
public:
    jump();
    ~jump();
    bool add_inst(short pc, instruction in_inst) override;
    short get_result() override;
};


#endif //COMPUTER_ARCHITECTURE_PROJECT_2_JUMP_H
