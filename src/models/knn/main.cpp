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


int main() {
  // Read and load dataset from csv
  string filename = string(DATA_DIR) + "email.csv";
  vector<vector<string>> data;
  data = read_csv(filename);
  // Split data into X and y
  auto [X, y] =  split_x_y(data, "Category");
  // Tokenize
  vector<vector<string>> X_processed = tokenize_dataset(X);

  auto [X_train, y_train, X_test, y_test] = train_test_split(X_processed, y, 0.8);

  vector<vector<double>> X_encoded_train, X_encoded_test;
  X_encoded_train = get_tf_idf_optimized(X_train);
  X_encoded_test = get_tf_idf_optimized(X_test);
  KNN knn;
  knn.fit(X_encoded_train, y_train);
  int correct {knn.predict(X_encoded_test, y_test)};
  std::cout << "Accuracy: " << (double) correct / X_test.size() << "%" << std::endl;
  return 0;
} 
