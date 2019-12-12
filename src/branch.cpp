//
// Created by solomspd on 03/12/2019.
//

#include "branch.h"

branch::branch() {
    taken = false;
    predict_taken = false;
    predict = 0;
    predict_tot = 0;
}

branch::branch(int c, short *in_pc) {
    branch();
    t_c = c;
    pc = in_pc;
}

branch::~branch() {

}

bool branch::add_inst(instruction in_inst) {
    if (busy) return false;
    busy = true;
    address = *pc + 1 + in_inst.imm;
    predict_tot++;
    predict_taken = in_inst.imm < 0;
    if (src1 == src2) {
        predict += predict_taken;
        *pc = address;
    }

    return true;
}

short branch::get_result() {

    return address;
}

float branch::get_pred(int &pred, int &pred_t) {
    pred += predict;
    pred_t += predict_tot;
    return predict / predict_tot;
}
