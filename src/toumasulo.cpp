//
// Created by solomspd on 03/12/2019.
//

#include <iostream>
#include "toumasulo.h"

toumasulo::toumasulo(std::string mem_file, int in_issue_n, int in_max_rob, int in_l_s, int in_s_s, int in_j_s, int in_b_s, int in_a_s, int in_n_s, int in_m_s, int in_l_c, int in_s_c, int in_j_c, int in_b_c, int in_a_c, int in_n_c,  int in_m_c) {

    rob_buffer.set_up(in_issue_n, in_max_rob, in_l_c, in_s_c, in_j_c, in_b_c, in_a_c, in_n_c, in_m_c);
    issue_n = in_issue_n;

    std::ifstream file(mem_file.c_str());
    lws = in_l_s;
    sws = in_s_s;
    js = in_j_s;
    bs = in_b_s;
    as = in_a_s;
    ns = in_n_s;
    mults = in_m_s;
    lwc = in_l_c;
    swc = in_s_c;
    jc = in_j_c;
    bc = in_b_c;
    ac = in_a_c;
    nc = in_n_c;
    mc = in_m_c;
    int i = 0;
    if (!file.is_open()) {
        std::cout << "CANNOT OPEN FILE";
    }
    while (!file.eof()) {
        file >> mem[i++];
    }
    file.close();

    cycle_n = 0;
    pc = new short (0);
    for (int i = 0; i < reg_count; i++) {
        reg_dep[i].first = false;
        reg_dep[i].second = new short*;
        *reg_dep[i].second = new short {0};
    }
    std::fill(std::begin(reg), std::end(reg), new short*{new short{0}});

    tot = lws + sws + js + bs + as+ ns + mults;
    stations = new station *[tot];
    int count = 0;

    // TODO pragmatically assign types so that it pragmatically creates stations
    int temp = count;
    for (int i = 0; i < lws; i++) {
        stations[count++] = new lw(lwc, mem);
    }
    l_st = temp;
    load = stations[temp];

    temp = count;
    for (int i = 0; i < sws; i++) {
        stations[count++] = new sw(swc, l_st, lws, stations);
    }
    s_st = temp;
    store = stations[temp];

    temp = count;
    for (int i = 0; i < js; i++) {
        stations[count++] = new jump(jc, pc);
    }
    j_st = temp;
    jmp = stations[temp];

    temp = count;
    for (int i = 0; i < bs; i++) {
        stations[count++] = new branch(bc, pc);
    }
    b_st = temp;
    beq = stations[temp];

    temp = count;
    for (int i = 0; i < as; i++) {
        stations[count++] = new arith(ac);
    }
    a_st = temp;
    ari = stations[temp];

    temp = count;
    for (int i = 0; i < ns; i++) {
        stations[count++] = new nand(nc);
    }
    n_st = temp;
    nd = stations[temp];

    temp = count;
    for (int i = 0; i < mults; i++) {
        stations[count++] = new mult(mc);
    }
    m_st = temp;
    mul = stations[temp];
}

toumasulo::~toumasulo() {

}


bool toumasulo::queue_inst(instruction in_inst) {
    if (!rob_buffer.is_available()) {
        return true;
    }



    if (in_inst.inst_t == j && in_inst.sub_type != jmpe) {
        in_inst.rs2 = 1;
    }

    bool dep1 = true;
    bool dep2 = true;

    short *&src1 = !reg_dep[in_inst.rs1].first ? *reg[in_inst.rs1] : *reg_dep[in_inst.rs1].second;
    short *&src2 = !reg_dep[in_inst.rs2].first ? *reg[in_inst.rs2] : *reg_dep[in_inst.rs2].second;
    

    station *reserved;
    reserved = nullptr;
    switch (in_inst.inst_t) {
        case l:
            for (int i = l_st; i < lws + l_st; i++) {
                if (stations[i]->add_inst(in_inst)) {
                    reserved = stations[i];
                    break;
                }
            }
            break;

        case s:
            for (int i = s_st; i < sws + s_st; i++) {
                if (stations[i]->add_inst(in_inst)) {
                    reserved = stations[i];
                    break;
                }
            }
            break;

        case j:
            for (int i = j_st; i < js + j_st; i++) {
                if (stations[i]->add_inst(in_inst)) {
                    reserved = stations[i];
                    switch (in_inst.sub_type) {
                        case jmpe: dep1 = false; dep2 = false; break;
                        case ret: dep2 = false;
                    }
                    break;
                }
            }
            break;

        case b:
            for (int i = b_st; i < bs + b_st; i++) {
                if (stations[i]->add_inst(in_inst)) {
                    reserved = stations[i];
                    break;
                }
            }
            break;

        case a:
            for (int i = a_st; i < as + a_st; i++) {
                if (stations[i]->add_inst(in_inst)) {
                    reserved = stations[i];
                    if (in_inst.sub_type == addi) {
                        dep2 = false;
                    }
                    break;
                }
            }
            break;

        case n:
            for (int i = n_st; i < ns + n_st; i++) {
                if (stations[i]->add_inst(in_inst)) {
                    reserved = stations[i];
                    break;
                }
            }
            break;

        case m:
            for (int i = m_st; i < mults + m_st; i++) {
                if (stations[i]->add_inst(in_inst)) {
                    reserved = stations[i];
                    break;
                }
            }
            break;
    }


    if (reserved != nullptr) {
        rob_buffer.reserve(reserved->get_dest(), in_inst.inst_t, reserved->res_ptr(), reg_dep);
        if (in_inst.inst_t == s) {reserved->set_entry(rob_buffer.top());}
        reserved->set_dep(dep1, dep2, src1, src2);
        reserved->start_up();
    }

    return reserved != nullptr;
}

bool toumasulo::adv_c() {
    cycle_n++;

    if (*pc < prog.size()) {
        bool taken = true;
        for (int i = 0; i < issue_n && taken; i++) {
            taken = queue_inst(prog[*pc]);
            if (taken) { (*pc)++; }
            taken &= !(prog[*pc].inst_t == b || prog[*pc].inst_t == j);
        }
    }

    for (int i = 0; i < tot; i++) {
        stations[i]->adv_c();
    }

    rob_buffer.adv_c(reg, reg_dep, mem);

    **reg[0] = 0;

    return *pc >= prog.size() && rob_buffer.is_empty();
}

void toumasulo::get_inst(std::vector<instruction> in_prog) {
    prog = in_prog;
}

void toumasulo::get_results(int &tot_c, float &ipc, float &predict) {
    tot_c = cycle_n;
    ipc = float(prog.size()) / float(cycle_n);
    int pred = 0;
    int pred_t = 0;
    for (int i = b_st; i < bs; i++) {
        stations[i]->get_pred(pred, pred_t);
    }
    if (pred_t > 0) {
        predict = pred / pred_t;
    } else {
        predict = -1;
    };
}
