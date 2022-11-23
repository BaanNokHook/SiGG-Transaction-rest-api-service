/**
 * @file HelperFunctions.hpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef HelperFunctions_h
#define HelperFunctions_h

#include "CompanyForecast.hpp"
#include "DataMatrix.hpp"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

std::vector<std::vector<double>> readDataFromFile(const std::string& fileName);
void showStockPortofolioPicks(std::vector<std::string>& companyNames, std::vector<double>& values);
std::vector<std::vector<double>> predictFutureValues(const std::string& fileName);

#endif /* HelperFunctions_h */
