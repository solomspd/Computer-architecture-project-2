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

    return false;
}

bool station::is_busy() {
    return busy;
}

int station::set_rob(short in) {
    return rob;
}
