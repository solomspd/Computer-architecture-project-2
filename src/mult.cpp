//
// Created by solomspd on 03/12/2019.
//

#include "mult.h"

mult::mult(int c) {
    t_c = c;
}

mult::~mult() {

}

bool mult::add_inst(instruction in_inst) {
    if (busy) { return false; }
    busy = true;
    dest = in_inst.rd;

    return true;
}

short mult::get_result() {
    return src1 * src2;
}
