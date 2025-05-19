#include <iostream>
#include <unordered_map>
#include <vector>
#include <random>

#include "ml_from_scratch_cpp/core/data/reading.h"
#include "ml_from_scratch_cpp/core/data/splitting.h"
#include "ml_from_scratch_cpp/core/data/text.h"
#include "ml_from_scratch_cpp/core/encoding/text_terms.h"
#include "ml_from_scratch_cpp/models/knn/knn.h"
using std::vector;
using std::unordered_map;
using std::string;
using vec_of_vec_str_map = vector<unordered_map<string, vector<string>>>; 


int main() {

 string filename = std::string(DATA_DIR) + "email.csv";
 vec_of_str_map data;
 data = read_csv(filename);
 vector<unordered_map<string, vector<string>>> processed = tokenize_dataset(data);


 vector<unordered_map<string, vector<double>>> encoded_data;
 encoded_data = get_tf_idf(processed);
 
 std::random_device rd;
 double ratio {0.8};
  std::default_random_engine rng(rd());
  std::shuffle(encoded_data.begin(), encoded_data.end(),  rng);
  double split_index {ratio * encoded_data.size()};
  vector<unordered_map<string, vector<double>>> train_data {encoded_data.begin(), encoded_data.begin() + (int) split_index};
  vector<unordered_map<string, vector<double>>> test_data {encoded_data.begin() + (int) split_index, encoded_data.end()};
 KNN knn;
 knn.fit(train_data);
 int correct {knn.predict(test_data)};
 std::cout << "Accuracy: " << (double) correct / test_data.size() << "%" << std::endl;
 
  return 0;
} 
