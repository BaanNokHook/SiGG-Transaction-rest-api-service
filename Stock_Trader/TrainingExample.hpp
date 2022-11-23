/**
 * @file TrainingExample.hpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef TrainingExample_hpp
#define TrainingExample_hpp

#include <stdio.h>
#include <vector>

class TrainingExample {
    
    std::vector<double> featureList;
    double yValue;
    
public:
    
    TrainingExample(const std::vector<double>& features, double tar);
    double getFeatureValue(int index) const;
    std::vector<double>& getAllFeatures();
    double getYValue() const;
    friend std::ostream& operator<<(std::ostream& outputStream, const TrainingExample& trainingData);
    
};

#endif /* TrainingExample_hpp */
