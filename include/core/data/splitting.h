#ifndef SPLITTING_H
#define SPLITTING_H
#include <utility>
#include <random>
#include <algorithm>
#include <set>


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
        return -1;
    }
    
    // Convert to lowercase for comparison
    auto to_lower = [](string str) {
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
        return str;
    };
    
    string target = to_lower(label);
    
    for (size_t i = 0; i < data[0].size(); ++i) {
        string header = to_lower(data[0][i]);
        
        // Remove whitespace
        header.erase(std::remove_if(header.begin(), header.end(), ::isspace), header.end());
        target.erase(std::remove_if(target.begin(), target.end(), ::isspace), target.end());
        
        if (header.find(target) != string::npos || target.find(header) != string::npos) {
            return static_cast<int>(i);
        }
    }
    
    return -1;
}

std::pair<vector<vector<string>>, vector<string>> split_x_y(const vector<vector<string>>& data, const string& label) {
    vector<vector<string>> X;
    vector<string> y;
    
    int idx = get_label_index(data, label);
    if (idx == -1) {
        std::cout << "didnt find label" << std::endl;
        return std::make_pair(X, y);
    }
    
    // Process all rows including header
    for (size_t row = 0; row < data.size(); ++row) {
        if (row == 0) {
            // Header row - don't add to y, just process X headers
            vector<string> x_header;
            for (size_t col = 0; col < data[row].size(); ++col) {
                if (col != static_cast<size_t>(idx)) {
                    x_header.push_back(data[row][col]);
                }
            }
            X.push_back(x_header);
        } else {
            // Data rows
            y.push_back(data[row][idx]);
            
            vector<string> x_row;
            for (size_t col = 0; col < data[row].size(); ++col) {
                if (col != static_cast<size_t>(idx)) {
                    x_row.push_back(data[row][col]);
                }
            }
            X.push_back(x_row);
        }
    }
    return std::make_pair(X, y);
}

std::tuple<vector<vector<string>>, vector<vector<string>>> extract_and_remove_columns(
    const vector<vector<string>>& data, 
    const vector<string>& column_names) {
    
    vector<vector<string>> extracted;
    vector<vector<string>> remaining;
    
    if (data.empty() || data[0].empty() || column_names.empty()) {
        return std::make_tuple(extracted, data); // Return empty extracted, original data
    }
    
    // Find indices of all requested columns
    vector<int> extract_indices;
    for (const string& col_name : column_names) {
        int idx = get_label_index(data, col_name);
        if (idx != -1) {
            extract_indices.push_back(idx);
        } else {
            std::cout << "Warning: Column '" << col_name << "' not found" << std::endl;
        }
    }
    
    if (extract_indices.empty()) {
        std::cout << "No valid columns found" << std::endl;
        return std::make_tuple(extracted, data);
    }
    
    // Create a set for faster lookup of indices to extract
    std::set<int> extract_set(extract_indices.begin(), extract_indices.end());
    
    // Process all rows (including header)
    for (size_t row = 0; row < data.size(); ++row) {
        vector<string> extracted_row;
        vector<string> remaining_row;
        
        for (size_t col = 0; col < data[row].size(); ++col) {
            if (extract_set.count(static_cast<int>(col))) {
                // This column should be extracted
                extracted_row.push_back(data[row][col]);
            } else {
                // This column should remain
                remaining_row.push_back(data[row][col]);
            }
        }
        
        extracted.push_back(extracted_row);
        remaining.push_back(remaining_row);
    }
    
    return std::make_tuple(extracted, remaining);
}
    


#endif
