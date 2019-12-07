//
// Created by solomspd on 03/12/2019.
//

#ifndef COMPUTER_ARCHITECTURE_PROJECT_2_STATION_H
#define COMPUTER_ARCHITECTURE_PROJECT_2_STATION_H

const short lwc = 3, swc = 3, jc = 1, bc = 1, ac = 2, nc = 1, mc = 10;

enum status {issue, execute, write, commit};

enum inst_type {
    l, s, j, b, a, n, m
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
    short dest; //destination register
    short rob;
    short res; //result
    short *dep1, *dep2; //dependencies
    bool busy;
    status cur_state;
public:
    station();
    ~station();
    bool adv_c();
    bool is_busy();
    int set_rob(short in);
    void set_dep(short *in_dep1, short *in_dep2);
    virtual short get_result();
    virtual bool add_inst(instruction in_inst);
    virtual bool add_inst(short pc, instruction in_inst);
};


#endif //COMPUTER_ARCHITECTURE_PROJECT_2_STATION_H
