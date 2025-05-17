#include <iostream>
#include <unordered_map>
#include <vector>

#include "ml_from_scratch_cpp/models/bayesian/naive_bayes.h" 
#include "ml_from_scratch_cpp/core/data/reading.h"
#include "ml_from_scratch_cpp/core/data/splitting.h"


using std::vector;
using std::unordered_map;
using std::string;
using vec_of_str_map = vector<unordered_map<string, string>>; 


int main() {

 string filename = std::string(DATA_DIR) + "email.csv";
 vec_of_str_map data;
 data = read_csv(filename);
 /*
 vec_of_str_map train_data, test_data;
 std::tie(train_data, test_data) = train_test_split(data, 0.8);

 NaiveBayes nb;
 nb.fit(train_data);
 int correct {nb.predict(test_data)};
 std::cout << "Accuracy: " << (double) correct / test_data.size() << "%" << std::endl;
 */
  return 0;
} 
