#include <iostream>
#include <unordered_map>
#include <vector>
#include <random>

#include "core/data/reading.h"
#include "core/data/splitting.h"
#include "core/data/text.h"
#include "core/encoding/text_terms.h"
#include "models/linear/lr.h"

using std::vector;
using std::unordered_map;
using std::string;


int main() {

 string filename = string(DATA_DIR) + "wage_predict.csv";
 vector<vector<string>> data;
 data = read_csv(filename);
 /*
 auto [X, y] =  split_x_y(data, "monthly_salary");
 std::cout << X.size() << std::endl;
 */
 for (const vector<string>& row : data) {
   for (const string& word : row) {
     std::cout << word << std::endl;
   }
 }
 /*
 auto [X_train, y_train, X_test, y_test] = train_test_split(X, y, 0.8);


 LinearRegression lr(0.001, 50);
 lr.fit(X_train);
 */
 return 0; 
}
