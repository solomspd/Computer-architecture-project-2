//
// Created by solomspd on 03/12/2019.
//

#ifndef COMPUTER_ARCHITECTURE_PROJECT_2_SW_H
#define COMPUTER_ARCHITECTURE_PROJECT_2_SW_H


#include "station.h"
#include "rob.h"

class sw : public station {
private:
    station **load;
    rob_entry *dest_mod;
    int lws;
    short address;
    int l_st;
public:
    sw();

    sw(int c, int in_l_st, int in_lws, station **in_load);

    ~sw();

    bool add_inst(instruction in_inst) override;

    short get_result() override;

    bool check_addr_dep() override;

    short set_entry(rob_entry &in_entry) override;
};


#endif //COMPUTER_ARCHITECTURE_PROJECT_2_SW_H
