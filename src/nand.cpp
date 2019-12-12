//
// Created by solomspd on 03/12/2019.
//

#include "nand.h"

nand::nand(int c) {
    t_c = c;
}

nand::~nand() {

}

bool nand::add_inst(instruction in_inst) {
    if (busy) { return false; }
    busy = true;
    dest = in_inst.rd;

    return true;
}

short nand::get_result() {
    return ~(src1 & src2);
}
