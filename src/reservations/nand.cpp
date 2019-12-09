//
// Created by solomspd on 03/12/2019.
//

#include "nand.h"

nand::nand() {
    t_c = nc;
}

nand::~nand() {

}

bool nand::add_inst(instruction in_inst) {
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

short nand::get_result() {
    return *res = ~(src1 & src2);
}
