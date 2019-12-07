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
        case execute: cur_c--;
        case write: res = get_result();
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
