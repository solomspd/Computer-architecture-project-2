//
// Created by solomspd on 03/12/2019.
//

#include "sw.h"

sw::sw() {

}

sw::~sw() {

}

bool sw::add_inst(short rs1, short rs2, short imm) {
    if (busy) {return false;}
    busy = true;
    src1 = rs1;
    src2 = rs2;
    address = src2 + imm;
    return false;
}
