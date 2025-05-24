#ifndef SPLITTING_H
#define SPLITTING_H
#include <utility>
#include <random>
#include <algorithm>

template<typename T, typename L>
std::tuple<T, L, T, L> train_test_split(const T& X, const L& y, double ratio) {
    if (X.size() != y.size()) {
        throw std::invalid_argument("X and y must have the same number of samples");
    }
    
    // Create indices and shuffle them
    std::vector<size_t> indices(X.size());
    std::iota(indices.begin(), indices.end(), 0);
    
    std::random_device rd;
    std::default_random_engine rng(rd());
    std::shuffle(indices.begin(), indices.end(), rng);
    
    size_t split_index = static_cast<size_t>(ratio * X.size());
    
    // Create train and test sets
    T X_train, X_test;
    L y_train, y_test;
    
    X_train.reserve(split_index);
    y_train.reserve(split_index);
    X_test.reserve(X.size() - split_index);
    y_test.reserve(X.size() - split_index);
    
    // Split data using shuffled indices
    for (size_t i = 0; i < split_index; ++i) {
        X_train.push_back(X[indices[i]]);
        y_train.push_back(y[indices[i]]);
    }
    
    for (size_t i = split_index; i < indices.size(); ++i) {
        X_test.push_back(X[indices[i]]);
        y_test.push_back(y[indices[i]]);
    }
    
    return std::make_tuple(X_train, y_train, X_test, y_test);
}

int get_label_index(const vector<vector<string>>& data, const string& label) {
    if (data.empty() || data[0].empty()) {
        return -1; // No data or empty first row
    }
    
    // Search in the first row (header row)
    auto it = std::find(data[0].begin(), data[0].end(), label);
    
    if (it != data[0].end()) {
        return it - data[0].begin(); // Return the index
    } else {
        return -1; // Label not found
    }
}

std::pair<vector<vector<string>>, vector<string>> split_x_y(const vector<vector<string>>& data, const string& label) {
    vector<vector<string>> X;
    vector<string> y;
    
    int idx = get_label_index(data, label);
    if (idx == -1) {
        return std::make_pair(X, y);
    }
    
    // Start from row 1 (skip header) and go to the end
    for (size_t row = 1; row < data.size(); ++row) {
        // Store the y value
        y.push_back(data[row][idx]);
        
        // Create X row by copying all columns except the y column
        vector<string> x_row;
        for (size_t col = 0; col < data[row].size(); ++col) {
            if (col != static_cast<size_t>(idx)) {
                x_row.push_back(data[row][col]);
            }
        }
        X.push_back(x_row);
    }
    return std::make_pair(X, y);
}
#endif
