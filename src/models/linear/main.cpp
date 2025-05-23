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

typedef vector<unordered_map<string, string>> str_omap_vector_t;
typedef vector<unordered_map<string, vector<string>>> dataset_vec_str_t;
typedef vector<unordered_map<string, vector<double>>> dataset_vec_double_t;

int main() {

 string filename = string(DATA_DIR) + "wage_predict.csv";
 vector<vector<string>> data;
 data = read_csv(filename);
 display_csv(data);

 /*
 dataset_vec_str_t processed = tokenize_dataset(data);
 dataset_vec_double_t encoded_data;
 encoded_data = get_tf_idf(processed);

 auto [train_data, test_data] = train_test_split(encoded_data, 0.8);

 LinearRegression lr(0.001, 50);
 lr.fit(train_data);
 */
 return 0; 
}
