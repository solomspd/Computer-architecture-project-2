//
// Created by solomspd on 03/12/2019.
//

#include "toumasulo.h"

toumasulo::toumasulo() {
    cycle_n = 0;
    pc = 0;
}

toumasulo::~toumasulo() {

}



bool toumasulo::queue_inst(instrucuton in_inst) {
    bool queued = true;
//    if (!rob.is_available()) {  // TODO add ROB checking implementation
//        return queued;
//    }
    switch(in_inst.inst_t) {
        case l: for (auto i: load) {
            if (i.add_inst(in_inst.rs1, in_inst.rd, in_inst.imm)) {
//                i.set_rob(rob.reserve(i)) // TODO rob function that reserves rob for new instruction
                queued = false;
                break;
            }
        }
        break;

        case s: for (auto i: store) {
            if (i.add_inst(in_inst.rs1, in_inst.rs2, in_inst.imm)) {
//                i.set_rob(rob.reseve(i))
                queued = false;
                break;
            }
        }
        break;

        case j: for (auto i: jmp) {
            if (i.add_inst(pc, in_inst.imm)) {
//                i.set_rob(rob.reserve(i));
                queued = false;
                break;
            }
        }
        break;

        case b: for (auto i: beq) {
            if (i.add_inst(pc, in_inst.rs1, in_inst.rs2, in_inst.imm)) {
//                i.set_rob(rob.reserve(i));
                queued = false;
                break;
            }
        }
        break;

        case a: for (auto i: ari) {
            if (i.add_inst(in_inst.rs1, in_inst.rs2, in_inst.rd)) {
//                i.set_rob(rob.reserve(i));
                queued = false;
                break;
            }
        }
        break;

        case n: for (auto i: nd) {
            if (i.add_inst(in_inst.rs1, in_inst.rs2, in_inst.rd)) {
//                i.set_rob(rob.reserve(i));
                queued = false;
                break;
            }
        }
        break;

        case m: for (auto i: mul) {
            if (i.add_inst(in_inst.rs1, in_inst.rs2, in_inst.rd)) {
//                i.set_rob(rob.reserve(i));
                queued = false;
                break;
            }
        }
        break;
    }
    return queued;
}
