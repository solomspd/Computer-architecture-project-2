//
// Created by solomspd on 03/12/2019.
//

#include "lw.h"

lw::lw() {
    t_c = lwc;
}

lw::~lw() {

}

bool lw::add_inst(short rs1, short rd, short imm) {
    if (busy) {return false;}
    busy = true;
    dest = rd;
    address = rs1 + imm;
    return true;
}

short lw::get_result() {
//    return access_memory(address);
}
