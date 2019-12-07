//
// Created by solomspd on 03/12/2019.
//

#include "jump.h"

jump::jump() {
    t_c = jc;
}

jump::~jump() {

}

bool jump::add_inst(short pc_in, instruction in_inst) {
    if (busy) {return false;}
    busy = true;
    address = pc_in + 1 + in_inst.imm;

    return true;
}

short jump::get_result() {
    // TODO figure out setting PC
    return address;
}
