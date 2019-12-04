//
// Created by solomspd on 03/12/2019.
//

#ifndef COMPUTER_ARCHITECTURE_PROJECT_2_STATION_H
#define COMPUTER_ARCHITECTURE_PROJECT_2_STATION_H

const short lwc = 3, swc = 3, jc = 1, bc = 1, ac = 2, nc = 1, mc = 10;

enum status {issue, execute, write, commit};


class station {
protected:
    short t_c, cur_c; //target and current cycles
    short src1, src2; //sources
    short dest; //destination register
    short rob;
    short res; //result
    short dep1, dept2; //dependencies
    bool busy;
    status cur_state;
public:
    station();
    ~station();
    bool adv_c();
    bool is_busy();
    int set_rob(short in);
};


#endif //COMPUTER_ARCHITECTURE_PROJECT_2_STATION_H
