//
// Created by solomspd on 03/12/2019.
//

#include "branch.h"

branch::branch() {
    t_c = bc;
    taken = false;
    predict_taken = false;
}

branch::branch(short *in_pc) {
    branch();
    pc = in_pc;
}

branch::~branch() {

}

bool branch::add_inst(instruction in_inst) {
    if (busy) return false;
    busy = true;
    address = *pc + 1 + in_inst.imm;
    if (dep1) {
        temp1 = in_inst.rs1;
    } else {
        src1 = *in_inst.rs2;
    }

    if (dep2) {
        temp1 = in_inst.rs2;
    } else {
        src2 = *in_inst.rs2;
    }

    if (src1 == src2) {
        *pc = address;
    }

    return true;
}

short branch::get_result() {
    return address;
}
