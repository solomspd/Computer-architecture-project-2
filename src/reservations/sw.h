//
// Created by solomspd on 03/12/2019.
//

#ifndef COMPUTER_ARCHITECTURE_PROJECT_2_SW_H
#define COMPUTER_ARCHITECTURE_PROJECT_2_SW_H


#include "station.h"

class sw : public station {
private:
    short address;
public:
    sw();
    ~sw();
    bool add_inst(instruction in_inst) override;
    short get_result() override;
};


#endif //COMPUTER_ARCHITECTURE_PROJECT_2_SW_H
