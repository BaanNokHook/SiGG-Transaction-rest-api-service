/**
 * @file DataMatrix.hpp
 * @author SiGG (Project::SiGG-Transaction-rest-api-service)
 * @brief 
 * @version 0.1
 * @date 2022-11-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef DataMatrix_hpp
#define DataMatrix_hpp

#include <stdio.h>
#include <iostream>
#include <vector>

class DataMatrix {
    
public:
    DataMatrix(const int row, const int column, const int value);
//    DataMatrix(const std::string& fileName);
    DataMatrix(const std::vector<std::vector<double>>& values);
    DataMatrix(const int row, const int column, const std::vector<std::vector<double>>& values);

    DataMatrix transpose();
    DataMatrix inverse();

    double operator()(const int& row, const int& column) const;
    
    friend std::ostream& operator<<(std::ostream& outputStream, const DataMatrix& dataMatrix);
    friend DataMatrix operator*(const DataMatrix& left, const DataMatrix& right);
    std::vector<double> getThetaValues();
    
    int getRows() const;
    int getColumns() const; 
    
private:
    std::vector<std::vector<double>> valueMatrix;
    int row;
    int column;
};

DataMatrix getUnitMatrix(int size);

#endif /* DataMatrix_hpp */
