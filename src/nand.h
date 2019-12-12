//
// Created by solomspd on 03/12/2019.
//

#ifndef COMPUTER_ARCHITECTURE_PROJECT_2_NAND_H
#define COMPUTER_ARCHITECTURE_PROJECT_2_NAND_H


#include "station.h"

class nand : public station {
private:

public:
    nand(int c);

    ~nand();

    bool add_inst(instruction in_inst) override;

    short get_result() override;
};


#endif //COMPUTER_ARCHITECTURE_PROJECT_2_NAND_H
