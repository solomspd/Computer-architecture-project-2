//
// Created by solomspd on 03/12/2019.
//

#include "station.h"

station::station() {
    cur_c = 0;
    busy = false;
    cur_state = issue;
}

station::~station() {

}

bool station::adv_c() {
    switch (cur_state) {
        case issue :
            if (dep1 == -1 && dep2 == -1) {
                cur_state = execute;
            }
            break;
        case execute:
            if (!cur_c--){
                cur_state = write;
            }
            break;
        case write: res = get_result();
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

void station::set_dep(short in_dep1, short in_dep2) {
    dep1 = in_dep1;
    dep2 = in_dep2;
}