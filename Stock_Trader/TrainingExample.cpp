/**
 * @file TrainingExample.cpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "TrainingExample.hpp"

TrainingExample::TrainingExample(const std::vector<double>& features, double tar) : featureList(features), yValue(tar) {}

// Get the value of a specific feature for this training example.
double TrainingExample::getFeatureValue(int index) const {
    return featureList[index];
}

// Get all the values of all the features for this training example.
std::vector<double>& TrainingExample::getAllFeatures() {
    return featureList;
}

// Get the F(features) value for this training example - the corresponding Y value. 
double TrainingExample::getYValue() const {
    return yValue;
}

std::ostream& operator<<(std::ostream& outputStream, const TrainingExample& trainingData) {
    
    return outputStream;
}
