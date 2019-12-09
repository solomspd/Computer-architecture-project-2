//
// Created by solomspd on 03/12/2019.
//

#include "sw.h"

sw::sw() {
    dest = 0;
    t_c = swc;
}

sw::~sw() {

}

bool sw::add_inst(instruction in_inst) {
    if (busy) {return false;}
    busy = true;
    if (dep1) {
        temp1 = in_inst.rs1;
    } else {
        src1 = *in_inst.rs1;
    }
    if (dep2) {
        temp2 = in_inst.rs1;
    } else {
        src2 = *in_inst.rs2;
    }
    address = src2 + in_inst.imm;

    return false;
}

short sw::get_result() {
    // mem[address] = src1;
    return;
}
