//
// Created by solomspd on 03/12/2019.
//

#include "jump.h"

jump::jump() {

}

jump::~jump() {

}

bool jump::add_inst(short pc_in, short imm) {
    if (busy) {return false;}
    busy = true;
    address = pc_in + 1 + imm;

    return true;
}
