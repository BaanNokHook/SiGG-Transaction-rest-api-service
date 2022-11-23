/**
 * @file Hypothesis.hpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef Hypothesis_hpp
#define Hypothesis_hpp

#include "TrainingExample.hpp"
#include "ConstantValues.hpp"
#include <stdio.h>
#include <vector>
#include <iostream>


class Hypothesis {
    
    std::vector<TrainingExample> trainingExamples;
    std::vector<double> thetaValues;
    size_t numberOfFeatures;
    size_t numberOfTrainingExamples;
    Constants constantValues;
    
    // To get computed Y - multiplication between theta and respective features of a given training example.
    double getComputedY(const std::vector<double>& newThetaValues, const std::vector<double>& featureList);
    
    // To get the square sum of (actual y - computed y) - aka the costFunction.
    double costFunction(int thetaNumber, const std::vector<double>& newThetaValues);
    
    void updateThetaValues(std::vector<double>& newThetaValues);
    
public:
    
    Hypothesis(std::vector<TrainingExample>& trainingData);
    std::vector<double> performGradientDescent();
    friend std::ostream& operator<<(std::ostream& outputStream, const Hypothesis& hypothesis);
};

#endif /* Hypothesis_hpp */
