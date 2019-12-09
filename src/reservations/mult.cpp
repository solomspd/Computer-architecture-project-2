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
    if (dep1) {
        temp1 = in_inst.rs1;
    } else {
        src1 = *in_inst.rs1;
    }

    if (dep2) {
        temp2 = in_inst.rs2;
    } else {
        src2 = *in_inst.rs2;
    }
    dest = in_inst.rd;
    
    return true;
}

short mult::get_result() {
    return *res = src1 * src2;
}
