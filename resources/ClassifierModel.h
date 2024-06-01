// ClassifierModel.h
#ifndef CLASSIFIER_MODEL_H
#define CLASSIFIER_MODEL_H

#include <onnxruntime_cxx_api.h>
#include <vector>
#include <iostream>
#include "Resource.h"
#include <string>

class ClassifierModel
{
private:
    Ort::Env env;
    Ort::SessionOptions session_options;
    Ort::Session session;

public:
    ClassifierModel(const std::string &model_path);
    ~ClassifierModel();

    std::string runInference(std::vector<float> &inputData);
};

#endif