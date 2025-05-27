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
#include "core/feature/manipulation.h"
#include "core/metrics/linear_metrics.h"


using std::vector;
using std::unordered_map;
using std::string;

#include <vector>
#include <numeric>
#include <cmath>



int main() {
    string filename = string(DATA_DIR) + "wage_predict.csv";
    vector<vector<string>> data = read_csv(filename);
    
    // Extract industry column from original data
    vector<string> cols = {"industry"};
    auto [to_encode, remaining_data] = extract_and_remove_columns(data, cols);
    // Split the remaining data
    auto [X, y] = split_x_y(remaining_data, "monthly_salary");
    
    // Now try the conversions
    vector<double> y_better = str_2_double_safe(y);
    
    vector<vector<double>> industry_encoded = one_hot_encoding(to_encode);
    
    vector<vector<double>> dataset_double;
    for (size_t i = 0; i < X.size(); ++i) {
        dataset_double.push_back(str_2_double_safe(X[i]));
    }
    
    vector<vector<double>> final_dataset_X = concatenate_matrices(industry_encoded, dataset_double);
    final_dataset_X.erase(final_dataset_X.begin());
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
