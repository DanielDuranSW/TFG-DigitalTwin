#ifndef IMU_ACQUISITION_H
#define IMU_ACQUISITION_H

#include "State.h"

class IMU_Acquisition : public State
{
public:
    IMU_Acquisition();
    virtual ~IMU_Acquisition();

    void run() override;
};

#endif
