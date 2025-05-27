#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

using std::vector;
using std::string;



vector<vector<double>> concatenate_matrices(const vector<vector<double>>& matrix1, 
                                          const vector<vector<double>>& matrix2) {
    if (matrix1.size() != matrix2.size()) {
        throw std::invalid_argument("Matrices must have the same number of rows");
    }
    
    vector<vector<double>> result;
    result.reserve(matrix1.size());
    
    for (size_t i = 0; i < matrix1.size(); ++i) {
        vector<double> combined_row;
        combined_row.reserve(matrix1[i].size() + matrix2[i].size());
        
        // Add all elements from matrix1[i]
        combined_row.insert(combined_row.end(), matrix1[i].begin(), matrix1[i].end());
        
        // Add all elements from matrix2[i]
        combined_row.insert(combined_row.end(), matrix2[i].begin(), matrix2[i].end());
        
        result.push_back(combined_row);
    }
    
    return result;
}

vector<double> str_2_double_safe(const vector<string>& y) {
    vector<double> result;
    for (size_t i = 0; i < y.size(); ++i) {
        try {
            if (y[i].empty()) {
                std::cout << "Empty string at index " << i << std::endl;
                result.push_back(0.0); // or handle as you prefer
            } else {
                result.push_back(std::stod(y[i]));
            }
        } catch (const std::exception& e) {
            std::cout << "Error at index " << i << ": '" << y[i] << "' - " << e.what() << std::endl;
            result.push_back(0.0); // or throw, or skip
        }
    }
    return result;
}
