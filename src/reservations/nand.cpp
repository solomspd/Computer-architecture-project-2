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
    src1 = in_inst.rs1;
    src2 = in_inst.rs2;
    dest = in_inst.rd;

    return true;
}

short nand::get_result() {
    return ~(src1 & src2);
}
