#include <iostream>
#include <vector>

#include "models/bayesian/naive_bayes.h" 
#include "core/data/reading.h"
#include "core/data/splitting.h"
#include "core/data/text.h"

using std::vector;
using std::string;


int main() {
  // Read and load dataset
  string filename = std::string(DATA_DIR) + "email.csv";
  vector<vector<string>> data;
  data = read_csv(filename);
  // Select the label and split into X and y 
  auto [X, y] = split_x_y(data, "Category");
  // Tokenize (split into individual words) X
  vector<vector<string>> X_processed = tokenize_dataset(X);
  // Make a train test split on both X and y
  X_processed.erase(X_processed.begin());
  auto[X_train, y_train, X_test, y_test] = train_test_split(X_processed, y, 0.8);
  // Instantiate the NaiveBayes model, fit and predict
  NaiveBayes nb;
  nb.fit(X_train, y_train);
  int correct {nb.predict(X_test, y_test)};
  // Display Accuracy
  std::cout << "Accuracy: " << (double) correct / X_test.size() << "%" << std::endl;
  return 0;
} 
