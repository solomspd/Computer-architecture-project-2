//
// Created by solomspd on 03/12/2019.
//

#ifndef COMPUTER_ARCHITECTURE_PROJECT_2_STATION_H
#define COMPUTER_ARCHITECTURE_PROJECT_2_STATION_H

#include "rob.h"


enum status {
    issue, execute, write
};



enum j_type {
    jmpe, jalr, ret
};

enum a_type {
    add, addi, sub
};

struct instruction {
    short rs1, rs2, rd, imm;
    inst_type inst_t;
    short sub_type;
};

class station {
protected:
    short t_c, cur_c; //target and current cycles
    short src1, src2; //sources
    short **temp1, **temp2;
    short dest; //destination register
    short rob;
    short *res; //result
    bool dep1, dep2;
    bool busy;
    status cur_state;
public:
    station();

    ~station();

    bool adv_c();

    bool is_busy();

    int set_rob(short in);

    void set_dep(bool in_dep1, bool in_dep2, short *&in_temp1, short *&in_temp2);

    virtual short get_result();

    virtual bool add_inst(instruction in_inst);

    virtual bool add_inst(short pc, instruction in_inst);

    void start_up();

    short *&res_ptr();

    virtual bool check_addr_dep();

    virtual short get_addr();

    short get_dest();

    virtual short set_entry(rob_entry &in_entry);

    virtual float get_pred(int &pred, int &pred_t);

};


#endif //COMPUTER_ARCHITECTURE_PROJECT_2_STATION_H
