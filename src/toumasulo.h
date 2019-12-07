//
// Created by solomspd on 03/12/2019.
//

#ifndef COMPUTER_ARCHITECTURE_PROJECT_2_TOUMASULO_H
#define COMPUTER_ARCHITECTURE_PROJECT_2_TOUMASULO_H

#include <numeric>
#include <queue>

#include "reservations/station.h"
#include "reservations/lw.h"
#include "reservations/sw.h"
#include "reservations/jump.h"
#include "reservations/branch.h"
#include "reservations/arith.h"
#include "reservations/nand.h"
#include "reservations/mult.h"

const short unit_counts[7] = {2, 2, 2, 2, 3, 2, 2};
const short lws = 2, sws = 2, js = 2, bs = 2, as = 3, ns = 2, mults = 2;
const short reg_count = 8;

class toumasulo {
private:
    int tot;
    station **stations;
    station *load;
    station *store;
    station *jmp;
    station *beq;
    station *ari;
    station *nd;
    station *mul;
    short reg[reg_count];
    short reg_dep[reg_count];
    int cycle_n;
    short pc;
    std::queue<short> write_queue;
public:
    toumasulo();

    ~toumasulo();

    bool queue_inst(instruction in_inst);

    void adv_c();
};


#endif //COMPUTER_ARCHITECTURE_PROJECT_2_TOUMASULO_H
