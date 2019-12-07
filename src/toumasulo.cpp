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

    mul = stations[count];
    for (int i = 0; i < mults; i++) {
        stations[count++] = new mult;
    }
}

toumasulo::~toumasulo() {

}


bool toumasulo::queue_inst(instruction in_inst) {
    bool queued = true;
//    if (!rob.is_available()) {  // TODO add ROB checking implementation
//        return queued;
//    }
    station *reserved;
    switch (in_inst.inst_t) {
        case l:
            for (int i = 0; i < lws; i++) {
                if (load[i].add_inst(in_inst)) {
//                i.set_dep(reg_dep[in_inst.rs1]);// TODO iron out dependency checking and assign it to station
//                i.set_rob(rob.reserve(i)) // TODO rob function that reserves rob for new instruction
                    queued = false;
                    reserved = load + i;
                    break;
                }
            }
            break;

        case s:
            for (int i = 0; i < sws; i++) {
                if (store[i].add_inst(in_inst)) {
//                i.set_dep(reg_dep[in_inst.rs1], reg_dep[in_inst.rs2]);
//                i.set_rob(rob.reserve(i));
                    reserved = store + i;
                    queued = false;
                    break;
                }
            }
            break;

        case j:
            for (int i = 0; i < js; i++) {
                if (jmp[i].add_inst(pc, in_inst)) {
//                i.set_rob(rob.reserve(i));
                    reserved = jmp + i;
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
                    reserved = beq + i;
                    break;
                }
            }
            break;

        case a:
            for (int i = 0; i < as; i++) {
                if (ari[i].add_inst(in_inst)) {
//                i.set_rob(rob.reserve(i));
                    queued = false;
                    reserved = ari + i;
                    break;
                }
            }
            break;

        case n:
            for (int i = 0; i < ns; i++) {
                if (nd[i].add_inst(in_inst)) {
//                i.set_rob(reg_dep[rob.reserve(i));
                    queued = false;
                    reserved = nd + i;
                    break;
                }
            }
            break;

        case m:
            for (int i = 0; i < mults; i++) {
                if (mul[i].add_inst(in_inst)) {
//                i.set_rob(rob.reserve(i));
                    queued = false;
                    reserved = mul + i;
                    break;
                }
            }
            break;
    }

    if (reserved != nullptr) { // UNUSED ELEMENTS OF INSTRUCTIONS ARE TO BE SET TO -1
        reserved->set_dep(in_inst.rs1 != -1 ? reg_dep[in_inst.rs1] : nullptr, in_inst.rs2 != -1 ? reg_dep[in_inst.rs2] : nullptr); // checks for dependencies through register/ROB table and assigns the according dependency. If instruction does not use rs1 or rs2 then it writes null, meaning there is no dependency
    }

    return queued;
}

void toumasulo::adv_c() {
    cycle_n++;
    pc += 4;
    for (int i = 0; i < tot; i++) {
        if (stations[i]->adv_c()) {
//            rob.update_reservation(station[i].get_result());        //TODO elaborate implementation. Update rob with resulting value from station
        }
    }
}
