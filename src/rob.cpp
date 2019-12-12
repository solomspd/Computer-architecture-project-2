//
// Created by solomspd on 10/12/2019.
//

#include "rob.h"

rob::rob() {
    sz = 0;
    stag_sz = 0;
    arr.resize(max);
}

rob::~rob() {

}

void rob::reserve(short in_rd, inst_type in_t, short *&res, std::pair<bool, short **> reg_dep[]) {
    arr.push_back(rob_entry{nullptr, in_rd, in_t});
    staging.emplace_back(&arr.back(), &res);
    reg_dep[in_rd].first = (in_rd != 0);
    reg_dep[in_rd].second = &arr.back().val;
    stag_sz++;
}

void rob::adv_c(short **reg[], std::pair<bool, short **> reg_dep[], short mem[]) {

    if (arr.front().val != nullptr) {
        switch (arr.front().inst_t) {
            case s:
                mem[arr.front().dest] = *arr.front().val;
                break;
            case b:
                break;
            default:
                **reg[arr.front().dest] = *arr.front().val;
                reg_dep[arr.front().dest].first = false;
                delete *reg_dep[arr.front().dest].second;
        }

        arr.front().val = nullptr;
        arr.pop_front();
        sz--;
    }

    int count = 1;
    for (int i = 0; i < stag_sz; i++) {
        if (*staging[i].second != nullptr) {
            staging[i].first->val = new short{**staging[i].second};
            delete *staging[i].second;
            *staging[i].second = nullptr;
            staging.erase(staging.begin() + i);
            if (count++ >= issue_n) { return; }
        }
    }
}

bool rob::is_available() {
    return sz < max;
}

rob_entry &rob::top() {
    return arr.back();
}

void
rob::set_up(int in_issue, int in_max, int in_lwc, int in_swc, int in_jc, int in_bc, int in_ac, int in_nc, int in_mc) {
    issue_n = in_issue;
    max = in_max;
}

bool rob::is_empty() {
    return arr.size() == 0;
}
