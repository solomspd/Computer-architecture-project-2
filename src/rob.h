//
// Created by solomspd on 10/12/2019.
//

#ifndef COMPUTER_ARCHITECTURE_PROJECT_2_ROB_H
#define COMPUTER_ARCHITECTURE_PROJECT_2_ROB_H

#include <queue>

enum inst_type {
    l, s, j, b, a, n, m
};

struct rob_entry {
    short *val;
    short dest;
    inst_type inst_t;
};

class rob {
private:
    std::deque<rob_entry> arr;
    std::vector<std::pair<rob_entry *, short **>> staging;
    int sz;
    int stag_sz;
    int max;
    int issue_n;
public:
    rob();

    ~rob();

    void reserve(short in_rd, inst_type in_t, short *&res, std::pair<bool, short **> reg_dep[]);

    void adv_c(short **reg[], std::pair<bool, short **> reg_dep[], short mem[]);

    bool is_available();

    rob_entry &top();

    void set_up(int in_issue, int in_max, int in_lwc, int in_swc, int in_jc, int in_bc, int in_ac, int in_nc, int in_mc);

    bool is_empty();

};


#endif //COMPUTER_ARCHITECTURE_PROJECT_2_ROB_H
