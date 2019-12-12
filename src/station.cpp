//
// Created by solomspd on 03/12/2019.
//

#include "station.h"

station::station() {
    cur_c = 0;
    busy = false;
    res = nullptr;
    temp1 = new short *;
    temp2 = new short *;
    dep1 = false;
    dep2 = false;
}

station::~station() {

}

bool station::adv_c() {
    switch (cur_state) {
        case issue :
            if (dep1) {
                if (*temp1 != nullptr) {
                    dep1 = false;
                    src1 = **temp1;
                }
            }
            if (dep2) {
                if (*temp1 != nullptr) {
                    dep2 = false;
                    src2 = **temp2;
                }
            }
            if (!dep1 && !dep2 && check_addr_dep() && busy) {
                cur_state = execute;
            }
            break;
        case execute:
            if (cur_c++ >= t_c -1) {
                cur_state = write;
                res = new short{get_result()};
            }
            break;
        case write:
            if (res == nullptr) {
                busy = false;
            }
            break;
    }
    return cur_state == write;
}

bool station::is_busy() {
    return busy;
}

int station::set_rob(short in) {
    return rob;
}

short station::get_result() {
    return *res;
}

void station::set_dep(bool in_dep1, bool in_dep2, short *&in_temp1, short *&in_temp2) {
    dep1 = in_dep1;
    temp1 = &in_temp1;
    dep2 = in_dep2;
    temp2 = &in_temp2;
}

short *&station::res_ptr() {
    return res;
}

void station::start_up() {
    cur_c = 0;
    cur_state = issue;
}

bool station::check_addr_dep() {
    return true;
}

short station::get_addr() {
    return 0;
}

short station::get_dest() {
    return dest;
}

short station::set_entry(rob_entry &in_entry) {
    return 0;
}

bool station::add_inst(instruction in_inst) {
    return false;
}

bool station::add_inst(short pc, instruction in_inst) {
    return false;
}

float station::get_pred(int &pred, int &pred_t) {
    return 0;
}
