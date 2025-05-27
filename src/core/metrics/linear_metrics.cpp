#include <vector>
#include <cmath>
#include <numeric>
#include <stdexcept>

using std::vector;

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


