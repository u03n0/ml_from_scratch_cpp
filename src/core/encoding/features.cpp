#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
std::vector<std::vector<double>> one_hot_encoding(const std::vector<std::vector<std::string>>& x) {
    // Step 1: Collect all unique values across all rows
    std::set<std::string> feature_values;
    for (const std::vector<std::string>& row : x) {
        for (const std::string& item : row) {
            feature_values.insert(item);
        }
    }
    
    // Step 2: Create mapping from value to index
    std::unordered_map<std::string, size_t> value_to_index;
    size_t index = 0;
    for (const std::string& value : feature_values) {
        value_to_index[value] = index++;
    }
    
    // Step 3: Create the result matrix
    size_t rows = x.size();
    size_t columns = feature_values.size();
    std::vector<std::vector<double>> matrix(rows, std::vector<double>(columns, 0.0));
    
    // Step 4: Fill in the one-hot encoding
    for (size_t i = 0; i < rows; i++) {
        for (const std::string& item : x[i]) {
            size_t col_index = value_to_index[item];
            matrix[i][col_index] = 1.0;
        }
    }
    
    return matrix;
}
p
