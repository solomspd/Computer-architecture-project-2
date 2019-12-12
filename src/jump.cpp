//
// Created by solomspd on 03/12/2019.
//

#include "jump.h"

jump::jump() {
}

jump::jump(int c, short *in_pc) {
    t_c = c;
    pc = in_pc;
}

jump::~jump() {

}

bool jump::add_inst(instruction in_inst) {
    if (busy) { return false; }
    busy = true;
    op = static_cast<j_type>(in_inst.sub_type);
    switch (op) {
        case jalr:
            address = *pc + 1;
            break;
        case jmpe:
            address = *pc + 1 + in_inst.imm;
            break;
        case ret:;
    }

    return true;
}

short jump::get_result() {
    switch (op) {
        case jmpe:
            return *pc = address;
        case jalr:
            *pc = src1;
            return address;
        case ret:
            return *pc = src1;
    }
}
