//
// Created by solomspd on 03/12/2019.
//

#include "branch.h"

branch::branch() {

}

branch::~branch() {

}

bool branch::add_inst(short pc, short rs1, short rs2, short imm) {
    if (busy) return false;
    busy = true;
    address = pc + 1 + imm;
    src1 = rs1;
    src2 = rs2;

    return true;
}
