//
// Created by solomspd on 03/12/2019.
//

#include "arith.h"

arith::arith(int c) {
    t_c = c;
}

arith::~arith() {

}

bool arith::add_inst(instruction in_inst) {
    if (busy) { return false; }
    busy = true;
    op = static_cast<a_type>(in_inst.sub_type);
    if (op == addi) {
        src2 = in_inst.imm;
    }
    dest = in_inst.rd;

    return true;
}

short arith::get_result() {
    switch (op) {
        case addi:
        case add:
            return src1 + src2;
        case sub:
            return src1 - src2;
    }
}
