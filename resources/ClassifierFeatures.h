// ClassifierFeatures.h
#ifndef CLASSIFIER_FEATURES_H
#define CLASSIFIER_FEATURES_H

#include <vector>
#include <numeric>
#include "Resource.h"
#include <fftw3.h>
#include <cmath>
#include <onnxruntime_cxx_api.h>

class ClassifierFeatures : public Resource
{
private:
public:
    ClassifierFeatures();
    ~ClassifierFeatures();

    int Feature1(std::vector<int> buffer_fsr_in_distal_phalanges);
    int calculateMean(const std::vector<int> &buffer);
    void Feature2and3(const std::vector<int> &buffer);
    void Feature4(const std::vector<int> &buffer_fsr_in_distal_phalanges, const std::vector<int> &buffer_fsr_in_calcaneus_talus);
};

#endif