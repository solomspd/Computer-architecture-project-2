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
    src1 = in_inst.rs1;
    src2 = in_inst.rs2;
    address = src2 + in_inst.imm;
    return false;
}

short sw::get_result() {
    // mem[address] = src1;
    return
}
