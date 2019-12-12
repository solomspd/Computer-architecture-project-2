//
// Created by solomspd on 03/12/2019.
//

#include "sw.h"

sw::sw() {
    dest = 0;
    dest_mod = nullptr;
}

sw::~sw() {

}

bool sw::add_inst(instruction in_inst) {
    if (busy) { return false; }
    busy = true;
    dest = in_inst.imm;

    return true;
}

short sw::get_result() {
    return src1;
}

bool sw::check_addr_dep() {
    if (!dep1 && dest_mod != nullptr) {dest_mod->dest = dest += src2;}
    for (int i = l_st; i < lws; i++) {
        if (load[i]->get_addr() == dest && load[i]->is_busy()) { return false; }
    }
    return true;
}

sw::sw(int c, int in_l_st, int in_lws, station **in_load) {
    l_st = in_l_st;
    lws = in_lws;
    load = in_load;
    t_c = c;
}

short sw::set_entry(rob_entry &in_entry) {
    dest_mod = &in_entry;
}
