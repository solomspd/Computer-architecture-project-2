//
// Created by solomspd on 03/12/2019.
//

#include "arith.h"

arith::arith() {
    t_c = ac;
}

arith::~arith() {

}

bool arith::add_inst(instruction in_inst) {
    if (busy) {return false;}
    busy = true;
    src1 = in_inst.rs1;
    src2 = in_inst.rs2;
    dest = in_inst.rd;

    return true;
}

short arith::get_result() {
    switch (op) {
        case add: return src1 + src2;
        case sub: return src1 - src2;
    }
}
