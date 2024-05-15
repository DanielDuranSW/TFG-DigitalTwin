// ClassifierFeatures.h
#ifndef CLASSIFIER_FEATURES_H
#define CLASSIFIER_FEATURES_H

#include <vector>
#include <numeric>
#include "Resource.h"

class ClassifierFeatures : public Resource
{
private:
public:
    ClassifierFeatures();
    ~ClassifierFeatures();

    void Feature1(std::vector<int> buffer_fsr_in_distal_phalanges, std::vector<int> buffer_fsr_in_mid_proximal_phalanges, std::vector<int> buffer_fsr_in_metatarsals, std::vector<int> buffer_fsr_in_tarsometatarsals, std::vector<int> buffer_fsr_in_calcaneus_talus, std::vector<int> buffer_imu_in_x, std::vector<int> buffer_imu_in_y, std::vector<int> buffer_imu_in_z);
    int calculateMean(const std::vector<int> &buffer);
};

#endif