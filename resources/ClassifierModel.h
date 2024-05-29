// ClassifierModel.h
#ifndef CLASSIFIER_MODEL_H
#define CLASSIFIER_MODEL_H

#include <onnxruntime_cxx_api.h>
#include <vector>
#include <iostream>
#include "Resource.h"

class ClassifierModel : public Resource
{
private:
public:
    ClassifierModel();
    ~ClassifierModel();

    std::string runInference(const std::vector<int> &inputData);
};

#endif