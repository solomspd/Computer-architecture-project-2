//
// Created by solomspd on 03/12/2019.
//

#include "mult.h"

mult::mult() {

}

mult::~mult() {

}

bool mult::add_inst(short rs1, short rs2, short rd) {
    if (busy) {return false;}
    busy = true;
    src1 = rs1;
    src2 = rs2;
    dest = rd;

    return true;
}