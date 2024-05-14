// LowLevelActivityClassifier.h
#ifndef LOW_LEVEL_ACTIVITY_CLASSIFIER_H
#define LOW_LEVEL_ACTIVITY_CLASSIFIER_H

#include "State.h"
#include "StateSignalHandler.h"
#include "ThreadsData.h"
#include <numeric>
#include "config.h"

void *low_level_activity_classifier_run(void *arg);
double calculateMean(const std::vector<int> &data, const std::vector<int> &positions);
void printVector(const std::vector<int> &vec, const char *vecName);

#endif