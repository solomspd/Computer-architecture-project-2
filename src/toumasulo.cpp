//
// Created by solomspd on 03/12/2019.
//

#include "toumasulo.h"

toumasulo::toumasulo() {
    cycle_n = 0;
    pc = 0;
    std::accumulate(unit_counts, unit_counts + 7, tot);
    stations = new station*[tot];
    int count  = 0;

    // TODO pragmatically assign types so that it pragmatically creates stations
    load = stations[count];
    for (int i = 0; i < lws; i++) {
        stations[count++] = new lw;
    }

    store = stations[count];
    for (int i = 0; i < sws; i++) {
        stations[count++] = new sw;
    }

    jmp = stations[count];
    for (int i = 0; i < js; i++) {
        stations[count++] = new jump;
    }

    beq = stations[count];
    for (int i = 0; i < bs; i++) {
        stations[count++] = new branch;
    }

    ari = stations[count];
    for (int i = 0; i < as; i++) {
        stations[count++] = new arith;
    }

    nd = stations[count];
    for (int i = 0; i < ns; i++) {
        stations[count++] = new nand;
    }

    nd = stations[count];
    for (int i = 0; i < mults; i++) {
        stations[count++] = new mult;
    }
}

toumasulo::~toumasulo() {

}


bool toumasulo::queue_inst(instrucuton in_inst) {
    bool queued = true;
//    if (!rob.is_available()) {  // TODO add ROB checking implementation
//        return queued;
//    }
    switch (in_inst.inst_t) {
        case l:
            for (int i = 0; i < lws; i++) {
                if (load->add_inst(in_inst)) {
//                i.set_dep(reg_dep[in_inst.rs1]);// TODO iron out dependency checking and assign it to station
//                i.set_rob(rob.reserve(i)) // TODO rob function that reserves rob for new instruction
                    queued = false;
                    break;
                }
            }
            break;

        case s:
            for (int i = 0; i < sws; i++) {
                if (store[i].add_inst(in_inst)) {
//                i.set_dep(reg_dep[in_inst.rs1], reg_dep[in_inst.rs2]);
//                i.set_rob(rob.reserve(i));
                    queued = false;
                    break;
                }
            }
            break;

        case j:
            for (int i = 0; i < js; i++) {
                if (jmp[i].add_inst(pc, in_inst)) {
//                i.set_rob(rob.reserve(i));
                    queued = false;
                    break;
                }
            }
            break;

        case b:
            for (int i = 0; i < bs; i++) {
                if (beq[i].add_inst(pc, in_inst)) {
//                i.set_rob(rob.reserve(i));
                    queued = false;
                    break;
                }
            }
            break;

        case a:
            for (int i = 0; i < as; i++) {
                if (ari[i].add_inst(in_inst)) {
//                i.set_rob(rob.reserve(i));
                    queued = false;
                    break;
                }
            }
            break;

        case n:
            for (int i = 0; i < ns; i++) {
                if (nd[i].add_inst(in_inst)) {
//                i.set_rob(rob.reserve(i));
                    queued = false;
                    break;
                }
            }
            break;

        case m:
            for (int i = 0; i < mults; i++) {
                if (mul[i].add_inst(in_inst)) {
//                i.set_rob(rob.reserve(i));
                    queued = false;
                    break;
                }
            }
            break;
    }
    return queued;
}

void toumasulo::adv_c() {
    cycle_n++;
    for (int i = 0; i < tot; i++) {
        stations[i]->adv_c();
    }
}
