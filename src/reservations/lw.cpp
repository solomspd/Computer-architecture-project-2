//
// Created by solomspd on 03/12/2019.
//

#include "lw.h"

lw::lw() {
    t_c = lwc;
}

lw::~lw() {

}

bool lw::add_inst(instruction in_inst) {
    if (busy) {return false;}
    busy = true;
    dest = in_inst.rd;
    address = in_inst.rs1 + in_inst.imm;
    return true;
}

short lw::get_result() {
//    return access_memory(address);
}
