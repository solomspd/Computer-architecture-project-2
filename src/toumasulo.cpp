//
// Created by solomspd on 03/12/2019.
//

#include "toumasulo.h"

/*
TODO THINGS WE NEED TO CONSIDER:
 * How to handle multiple stations trying to write in the same cycle. Convention is writing the oldest first.
 * How should we write to the rob? should we give the reservation station a pointer to the int variable it will eventually change? will we update it with a method from the station?
 * How will we update from the rob the dependent stations?
*/
toumasulo::toumasulo() {
    cycle_n = 0;
    pc = 0;
    std::fill(std::begin(reg_dep), std::end(reg_dep), new short {0});
    std::fill(std::begin(reg), std::end(reg), new short {0});

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
        stations[count++] = new jump(pc);
    }

    beq = stations[count];
    for (int i = 0; i < bs; i++) {
        stations[count++] = new branch(pc);
    }

    ari = stations[count];
    for (int i = 0; i < as; i++) {
        stations[count++] = new arith;
    }

    nd = stations[count];
    for (int i = 0; i < ns; i++) {
        stations[count++] = new nand;
    }

    mul = stations[count];
    for (int i = 0; i < mults; i++) {
        stations[count++] = new mult;
    }
}

toumasulo::~toumasulo() {

}


bool toumasulo::queue_inst(instruction in_inst) {
//    if (!rob.is_available()) {  // TODO add ROB checking implementation
//        return true;
//    }
    short rs1 = *in_inst.rs1;
    short rs2 = *in_inst.rs2;

    bool dep1 = reg_dep[rs1].first;
    bool dep2 = reg_dep[rs2].first;

    if (!reg_dep[rs1].first) {
        in_inst.rs1 = reg[rs1];
    } else {
        in_inst.rs1 = reg_dep[rs1].second;
    }
    if (!reg_dep[rs2].first) {
        in_inst.rs2 = reg[rs2];
    } else {
        in_inst.rs2 = reg_dep[rs2].second;
    }

    station *reserved = nullptr;
    switch (in_inst.inst_t) {
        case l:
            for (int i = 0; i < lws; i++) {
                if (load[i].add_inst(in_inst)) {
                    reserved = load + i;
                    dep1 = false;
                    break;
                }
            }
            break;

        case s:
            for (int i = 0; i < sws; i++) {
                if (store[i].add_inst(in_inst)) {
                    reserved = store + i;
                    break;
                }
            }
            break;

        case j:
            for (int i = 0; i < js; i++) {
                if (jmp[i].add_inst(in_inst)) {
                    reserved = jmp + i;
                    dep1 = false;
                    dep2 = false;
                    break;
                }
            }
            break;

        case b:
            for (int i = 0; i < bs; i++) {
                if (beq[i].add_inst(in_inst)) {
                    reserved = beq + i;
                    break;
                }
            }
            break;

        case a:
            for (int i = 0; i < as; i++) {
                if (ari[i].add_inst(in_inst)) {
                    reserved = ari + i;
                    if (in_inst.sub_type /*== ADDI*/) {
                        dep2 = false;
                    }
                    break;
                }
            }
            break;

        case n:
            for (int i = 0; i < ns; i++) {
                if (nd[i].add_inst(in_inst)) {
                    reserved = nd + i;
                    break;
                }
            }
            break;

        case m:
            for (int i = 0; i < mults; i++) {
                if (mul[i].add_inst(in_inst)) {
                    reserved = mul + i;
                    break;
                }
            }
            break;
    }

    

    // ROB.reserve(reserved);
    if (reserved != nullptr) {
        reserved->set_dep(dep1, dep2);
    }

    return reserved == nullptr;
}

void toumasulo::adv_c() {
    cycle_n++;
    pc++;

    for (int i = 0; i < tot; i++) {
        stations[i]->adv_c();
    }
}
