//
// Created by solomspd on 03/12/2019.
//

#include "lw.h"

lw::lw() {

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
