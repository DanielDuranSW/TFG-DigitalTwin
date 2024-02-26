#ifndef ENERGY_SAVING_H
#define ENERGY_SAVING_H

#include "State.h"

class Energy_Saving : public State
{
public:
    Energy_Saving();
    virtual ~Energy_Saving();

    void run() override;
};

#endif
