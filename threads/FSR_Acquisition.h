// FSR_Acquisition.h
#ifndef FSR_ACQUISITION_H
#define FSR_ACQUISITION_H

#include "State.h"

class FSR_Acquisition : public State
{
public:
    FSR_Acquisition();
    virtual ~FSR_Acquisition();

    void run() override;
};

#endif
