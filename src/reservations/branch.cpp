//
// Created by solomspd on 03/12/2019.
//

#include "branch.h"

branch::branch() {
    t_c = bc;
}

branch::~branch() {

}

bool branch::add_inst(short pc, instruction in_inst) {
    if (busy) return false;
    busy = true;
    address = pc + 1 + in_inst.imm;
    src1 = in_inst.rs1;
    src2 = in_inst.rs2;

    return true;
}

short branch::get_result() {
    return address;
}
