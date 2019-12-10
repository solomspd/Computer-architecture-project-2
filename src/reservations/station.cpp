//
// Created by solomspd on 03/12/2019.
//

#include "station.h"

station::station() {
    cur_c = 0;
    busy = false;
    cur_state = issue;
    res = new short;
}

station::~station() {

}

bool station::adv_c() {
    switch (cur_state) {
        case issue :     
            if (dep1) {
                if (temp1 != nullptr) {
                    dep1 = false;
                    src1 = *temp1;
                }
            }
            if (dep2) {
                if (temp2 != nullptr) {
                    dep2 = false;
                    src2 = *temp2;
                }
            }
            if (!dep1 && !dep2 && sw_dep()) {
                cur_state = execute;
            }
            break;
        case execute:
            if (!cur_c--){
                cur_state = write;
            }
            break;
        case write: res = new short {get_result()};
            busy = false;
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
    return 0;
}

void station::set_dep(bool in_dep1, bool in_dep2) {
    dep1 = in_dep1;
    dep2 = in_dep2;
}

short *station::res_ptr() {
    return res;
}