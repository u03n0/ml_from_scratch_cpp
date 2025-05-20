#include <iostream>
#include <unordered_map>
#include <vector>
#include <random>

#include "core/data/reading.h"
#include "core/data/splitting.h"
#include "core/data/text.h"
#include "core/encoding/text_terms.h"
#include "models/knn/knn.h"
using std::vector;
using std::unordered_map;
using std::string;

typedef vector<unordered_map<string, string>> str_omap_vector_t;
typedef vector<unordered_map<string, vector<string>>> dataset_vec_str_t;
typedef vector<unordered_map<string, vector<double>>> dataset_vec_double_t;

int main() {

 string filename = string(DATA_DIR) + "email.csv";
 str_omap_vector_t data;
 data = read_csv(filename);
 dataset_vec_str_t processed = tokenize_dataset(data);


 dataset_vec_double_t encoded_data;
 encoded_data = get_tf_idf(processed);

 auto [train_data, test_data] = train_test_split(encoded_data, 0.8);

 KNN knn;
 knn.fit(train_data);
 int correct {knn.predict(test_data)};
 std::cout << "Accuracy: " << (double) correct / test_data.size() << "%" << std::endl;
 
  return 0;
} 
