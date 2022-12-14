/**
 * @file HelperFunctions.cpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include "HelperFunctions.h"
#include "CompanyForecast.hpp"
#include "DataMatrix.hpp"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

vector<vector<double>> readDataFromFile(const string& fileName) {
    ifstream fileInput (fileName+".csv");
    
    if (!fileInput) {
        cout << "Data from the file \"" << fileName << "\" could not be read." << endl;
        exit(1);
    }
    
    vector<vector<double>> predictionData;
    vector<double> dataValues;
    string value = "";
    
    // To check for Byte Order Mark (BOM).
    
    char bomCheck[4] = {0};
    fileInput.read(bomCheck, 3);
    if (strcmp(bomCheck, "\xEF\xBB\xBF") != 0) {
        fileInput.seekg(0);
    }
    
    while (fileInput >> value) {
        value = value + ",end,";
        string tableValue;
        stringstream ss = stringstream(value);
        while (getline(ss, tableValue, ',')) {
            if (tableValue == "end") {
                predictionData.push_back(dataValues);
                dataValues = {};
                continue;
            }
            
            try {
                dataValues.push_back(stod(tableValue));
            }
            catch (invalid_argument) {
                cout << "Invalid Sheet: " << fileName;
                exit(1);
            }
        }
    }
    return predictionData;
}

void showStockPortofolioPicks(vector<string>& companyNames, vector<double>& values) {
    if (companyNames.size() != values.size()) {
        cout << "Size of 'Company Names' Vector and 'Predicted Values' Vector is not the same - Size Mismatch." << endl << "Cannot perform portfolio operations on provided dataset vectors.";
        return;
    }
    for (int i = 0; i < values.size()-1; i++) {
        for (int j = 0; j < values.size()-1; j++) {
            if (values[j] < values[j+1]) {
                swap(values[j], values[j+1]);
                swap(companyNames[j], companyNames[j+1]);
            }
        }
    }
    
    for (int i = 0; i < values.size(); i++) {
        cout << companyNames[i] << ":   " << values[i] << endl;
    }
}

vector<vector<double>> predictFutureValues(const string& fileName) {
    vector<vector<double>> dataForTraining = readDataFromFile(fileName);
    vector<vector<double>> dataForPrediction = readDataFromFile(fileName+" Prediction");
    for (int n = 0; n < dataForPrediction.size(); n++) {
        vector<vector<double>> yValues;
        vector<vector<double>> dataForTrainingModel = dataForTraining;
        cout << dataForTrainingModel.size() << endl;
        for (int i = 0; i < dataForTrainingModel.size(); i++) {
            vector<double> test;
            test.push_back(dataForTrainingModel[i].back());
            dataForTrainingModel[i].pop_back();
            yValues.push_back(test);
        }
        DataMatrix y = DataMatrix(yValues);
        DataMatrix x = DataMatrix(dataForTrainingModel);
        
        CompanyForecast forecaster = CompanyForecast((((x.transpose() * x).inverse() * x.transpose()) * y).getThetaValues(), fileName);
        dataForPrediction[n].push_back(forecaster.returnCompanyForecast(dataForPrediction[n]));
        dataForTraining.push_back(dataForPrediction[n]);
        
    }
    return dataForTraining;
}
