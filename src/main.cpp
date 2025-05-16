#include <iostream>
#include <unordered_map>
#include <vector>
#include "../include/processing.h"
#include "../include/algo.h"

using std::vector;
using std::unordered_map;
using std::string;
using vec_of_vec_str_map = vector<unordered_map<string, vector<string>>>; 

int main() {

 string filename {"../email.csv"};
 vec_of_vec_str_map data;
 data = parseCSV(filename);
 vec_of_vec_str_map train_data, test_data;
 std::tie(train_data, test_data) = train_test_split(data, 0.8);

 NaiveBayes nb;
 nb.fit(train_data);
 int correct {nb.predict(test_data)};
 std::cout << "Accuracy: " << (double) correct / test_data.size() << "%" << std::endl;
  return 0;
} 
