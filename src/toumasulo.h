//
// Created by solomspd on 03/12/2019.
//

#ifndef COMPUTER_ARCHITECTURE_PROJECT_2_TOUMASULO_H
#define COMPUTER_ARCHITECTURE_PROJECT_2_TOUMASULO_H

#include <numeric>
#include <queue>
#include <string>
#include <fstream>

#include "station.h"
#include "lw.h"
#include "sw.h"
#include "jump.h"
#include "branch.h"
#include "arith.h"
#include "nand.h"
#include "mult.h"
#include "rob.h"

const short reg_count = 8;
const int mem_sz = 1e4;


class toumasulo {
private:
    int l_st, s_st, j_st, b_st, a_st, n_st, m_st;
    int lwc, swc, jc, bc, ac, nc, mc;
    int issue_n;
    int lws = 2, sws = 2, js = 2, bs = 2, as = 3, ns = 2, mults = 2;

    int tot;
    station **stations;
    station *load;
    station *store;
    station *jmp;
    station *beq;
    station *ari;
    station *nd;
    station *mul;
    short **reg[reg_count];
    std::pair<bool, short **> reg_dep[reg_count];
    int cycle_n;
    short *pc;
    rob rob_buffer;
    short mem[mem_sz];
    std::vector<instruction> prog;

public:
    toumasulo(std::string in_file, int in_issue_n = 2, int in_max_rob = 8, int in_l_s = 2 , int in_s_s = 2, int in_j_s = 2, int in_b_s = 2, int in_a_s = 3, int in_n_s = 2, int in_m_s = 2, int in_l_c = 3, int in_s_c = 3, int in_j_c = 1, int in_b_c = 1, int in_a_c = 2, int in_n_c = 1,  int in_m_c = 10);

    ~toumasulo();

    bool queue_inst(instruction in_inst);

    bool adv_c();

    void get_inst(std::vector<instruction> in_prog);

    void get_results(int &tot_c, float &ipc, float &predict);
};


#endif //COMPUTER_ARCHITECTURE_PROJECT_2_TOUMASULO_H
