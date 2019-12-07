//
// Created by solomspd on 03/12/2019.
//

#include "arith.h"

arith::arith() {
    t_c = ac;
}

arith::~arith() {

}

bool arith::add_inst(short rs1, short rs2, short rd) {
    if (busy) {return false;}
    busy = true;
    src1 = rs1;
    src2 = rs2;
    dest = rd;

    return true;
}

short arith::get_result() {
    switch (op) {
        case add: return src1 + src2;
        case sub: return src1 - src2;
    }
}
