#include <iostream>
#include <unordered_map>
#include <vector>
#include <random>

#include "core/data/reading.h"
#include "core/data/splitting.h"
#include "core/data/text.h"
#include "core/encoding/text_terms.h"
#include "models/linear/lr.h"
#include "core/encoding/features.h"
using std::vector;
using std::unordered_map;
using std::string;

#include <vector>
#include <numeric>
#include <cmath>
#include <stdexcept>

// Calculate Mean Absolute Error (MAE)
double calculate_mae(const std::vector<double>& y_true, const std::vector<double>& y_pred) {
    if (y_true.size() != y_pred.size()) {
        throw std::invalid_argument("Vectors must have the same size");
    }
    
    if (y_true.empty()) {
        throw std::invalid_argument("Vectors cannot be empty");
    }
    
    double sum_abs_errors = 0.0;
    for (size_t i = 0; i < y_true.size(); ++i) {
        sum_abs_errors += std::abs(y_true[i] - y_pred[i]);
    }
    
    return sum_abs_errors / y_true.size();
}

// Calculate R-squared (R²)
double calculate_r2(const std::vector<double>& y_true, const std::vector<double>& y_pred) {
    if (y_true.size() != y_pred.size()) {
        throw std::invalid_argument("Vectors must have the same size");
    }
    
    if (y_true.empty()) {
        throw std::invalid_argument("Vectors cannot be empty");
    }
    
    // Calculate mean of true values
    double mean_true = std::accumulate(y_true.begin(), y_true.end(), 0.0) / y_true.size();
    
    // Calculate sum of squares
    double ss_res = 0.0;  // Sum of squares of residuals
    double ss_tot = 0.0;  // Total sum of squares
    
    for (size_t i = 0; i < y_true.size(); ++i) {
        ss_res += std::pow(y_true[i] - y_pred[i], 2);
        ss_tot += std::pow(y_true[i] - mean_true, 2);
    }
    
    // Handle edge case where ss_tot is zero (all y_true values are the same)
    if (ss_tot == 0.0) {
        return (ss_res == 0.0) ? 1.0 : 0.0;
    }
    
    return 1.0 - (ss_res / ss_tot);
}
double calculate_rmse(const vector<double>& y_true, const vector<double>& y_pred) {
    if (y_true.size() != y_pred.size()) {
        throw std::invalid_argument("Vectors must be same size");
    }
    
    double sum_squared_error = 0.0;
    for (size_t i = 0; i < y_true.size(); ++i) {
        double error = y_true[i] - y_pred[i];
        sum_squared_error += error * error;
    }
    
    return std::sqrt(sum_squared_error / y_true.size());
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
int main() {
    string filename = string(DATA_DIR) + "wage_predict.csv";
    vector<vector<string>> data = read_csv(filename);
    
    std::cout << "Original data size: " << data.size() << " rows" << std::endl;
    if (!data.empty()) {
        std::cout << "First row (headers): ";
        for (const string& header : data[0]) {
            std::cout << "'" << header << "' ";
        }
        std::cout << std::endl;
    }

    // Extract industry column from original data
    vector<string> cols = {"industry"};
    auto [to_encode, remaining_data] = extract_and_remove_columns(data, cols);
    
    std::cout << "to_encode size: " << to_encode.size() << " rows" << std::endl;
    std::cout << "remaining_data size: " << remaining_data.size() << " rows" << std::endl;

    // Split the remaining data
    auto [X, y] = split_x_y(remaining_data, "monthly_salary");
    
    std::cout << "X size: " << X.size() << " rows" << std::endl;
    std::cout << "y size: " << y.size() << " elements" << std::endl;
    
    // Check first few y values
    std::cout << "First few y values:" << std::endl;
    for (size_t i = 0; i < std::min(size_t(5), y.size()); ++i) {
        std::cout << "y[" << i << "] = '" << y[i] << "'" << std::endl;
    }
    
    // Check first few X rows
    std::cout << "First X row:" << std::endl;
    if (!X.empty()) {
        for (size_t i = 0; i < std::min(size_t(5), X[0].size()); ++i) {
            std::cout << "X[0][" << i << "] = '" << X[0][i] << "'" << std::endl;
        }
    }

    // Now try the conversions
    std::cout << "\n=== Converting y to double ===" << std::endl;
    vector<double> y_better = str_2_double_safe(y);
    
    std::cout << "\n=== One-hot encoding industry ===" << std::endl;
    vector<vector<double>> industry_encoded = one_hot_encoding(to_encode);
    std::cout << "Industry encoded size: " << industry_encoded.size() << " rows" << std::endl;
    
    std::cout << "\n=== Converting X to double ===" << std::endl;
    vector<vector<double>> dataset_double;
    for (size_t i = 0; i < X.size(); ++i) {
        std::cout << "Converting X row " << i << std::endl;
        dataset_double.push_back(str_2_double_safe(X[i]));
    }
    
    std::cout << "\n=== Concatenating matrices ===" << std::endl;
    vector<vector<double>> final_dataset_X = concatenate_matrices(industry_encoded, dataset_double);
    final_dataset_X.erase(final_dataset_X.begin());
std::cout << "X : " << final_dataset_X.size() << " and y : " << y_better.size() << std::endl;
    auto [X_train, y_train, X_test, y_test] = train_test_split(final_dataset_X, y_better, 0.8);
    LinearRegression lr(0.001, 50);
    lr.fit(X_train, y_train);
    vector<double> idk = lr.predict(X_test);
    double rmse = calculate_rmse(y_test, idk);
    double mae = calculate_mae(y_test, idk);
    double r2 = calculate_r2(y_test, idk);

    std::cout << "MAE: " << mae << std::endl;
    std::cout << "RMSE: " << rmse << std::endl;
    std::cout << "R-squared: " << r2 << std::endl;
    return 0;
}
