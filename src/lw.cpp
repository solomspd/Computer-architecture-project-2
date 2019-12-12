//
// Created by solomspd on 03/12/2019.
//

#include "lw.h"

lw::lw() {
}

lw::lw(int c, short *in_mem) {
    lw();
    t_c = c;
    mem = in_mem;
}

lw::~lw() {

}

bool lw::add_inst(instruction in_inst) {
    if (busy) { return false; }
    busy = true;
    dest = in_inst.rd;
    address = in_inst.imm;

    return true;
}

short lw::get_result() {
    return mem[address += src1];
}

short lw::get_addr() {
    return address;
}
