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
    if (dep1) {
        temp1 = in_inst.rs1;
    }else {
        src1 = *in_inst.rs1;
    }
    return true;
}

bool lw::get_dep1() {
    if (dep1) {return true;}
    address = src1 + 1 = 
    return false;
}

short lw::get_result() {
//    return access_memory(address);
}
