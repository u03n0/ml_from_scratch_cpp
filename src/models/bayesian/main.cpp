#include <iostream>
#include <unordered_map>
#include <vector>

#include "models/bayesian/naive_bayes.h" 
#include "core/data/reading.h"
#include "core/data/splitting.h"
#include "core/data/text.h"

using std::vector;
using std::unordered_map;
using std::string;

typedef vector<unordered_map<string, string>> str_omap_vector_t;
typedef vector<unordered_map<string, vector<string>>> dataset_vec_str_t;

int main() {

 string filename = std::string(DATA_DIR) + "email.csv";
 str_omap_vector_t data;
 data = read_csv(filename);
 dataset_vec_str_t processed = tokenize_dataset(data);

 auto[train_data, test_data] = train_test_split(processed, 0.8);

 NaiveBayes nb;
 nb.fit(train_data);
 int correct {nb.predict(test_data)};
 std::cout << "Accuracy: " << (double) correct / test_data.size() << "%" << std::endl;
 
  return 0;
} 
