//
// Created by solomspd on 03/12/2019.
//

#include "mult.h"

mult::mult() {
    t_c = mc;
}

mult::~mult() {

}

bool mult::add_inst(instruction in_inst) {
    if (busy) {return false;}
    busy = true;
    src1 = in_inst.rs1;
    src2 = in_inst.rs2;
    dest = in_inst.rd;

    return true;
}

short mult::get_result() {
    return src1 * src2;
}
