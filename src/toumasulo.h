//
// Created by solomspd on 03/12/2019.
//

#ifndef COMPUTER_ARCHITECTURE_PROJECT_2_TOUMASULO_H
#define COMPUTER_ARCHITECTURE_PROJECT_2_TOUMASULO_H

#include "reservations/station.h"
#include "reservations/lw.h"
#include "reservations/sw.h"
#include "reservations/jump.h"
#include "reservations/branch.h"
#include "reservations/arith.h"
#include "reservations/nand.h"
#include "reservations/mult.h"

const short lws = 2, sws = 2, js = 2, bs = 2, as = 3, ns=2, mults = 2;
const short reg_count = 8;
enum inst_type{l, s, j, b, a, n, m};

struct instrucuton {
    short rs1, rs2, rd, imm;
    inst_type inst_t;
    short sub_type;
};

class toumasulo {
private:
    lw load[lws];
    sw store[sws];
    jump jmp[js];
    branch beq[bs];
    arith ari[as];
    nand nd[ns];
    mult mul[mults];
    short reg[reg_count];
    int cycle_n;
    short pc;
public:
    toumasulo();
    ~toumasulo();
    bool queue_inst(instrucuton in_inst)
};


#endif //COMPUTER_ARCHITECTURE_PROJECT_2_TOUMASULO_H
