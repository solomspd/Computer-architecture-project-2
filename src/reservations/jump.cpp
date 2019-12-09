//
// Created by solomspd on 03/12/2019.
//

#include "jump.h"

jump::jump() {
    t_c = jc;
}

jump::jump(short *in_pc) {
    jump();
    pc = in_pc;
}

jump::~jump() {

}

bool jump::add_inst(instruction in_inst) {
    if (busy) {return false;}
    busy = true;
    address = *pc + 1 + in_inst.imm;

    return true;
}

short jump::get_result() {
    return *pc = address;
}
