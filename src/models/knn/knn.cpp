#include <vector>
#include <string>
#include <unordered_map>
#include <cmath>
#include <algorithm>
#include "ml_from_scratch_cpp/models/knn/knn.h"


KNN::KNN(int x) {  
  k = x;
}

  string KNN::get_marjority_class(vector<unordered_map<double, string>> distances) {
    unordered_map<string, int> result;
    for (const unordered_map<double, string>& dict : distances) {
      for (const auto& it : dict) {
        if (std::find(result.begin(), result.end(), it.second) == result.end()) {
            result[it.second] = 1;
          } else {
            result[it.second]++;
          }
      }
    }
    int curr {0};
    string majority;
    for (const auto& it : result) {
  if (it.second > curr) {
        curr = it.second;
        majority = it.first;
      }
    }
    return majority;
}

string KNN::classify_point(vector<double> point){
    vector<double> distances;
    for (const unordered_map<string , vector<double>>& dict : points) {
        for (const auto& it : dict) {
            double dist = cosine_similarity(point, it.second, point.size());
            unordered_map<double, string> res = {dist, it.first};
            distances.push_back(res);
          }
    }
    std::sort(distances.begin(), distances.end(), comp);
    vector<double> sv(distances.begin(), distances.begin() + k);
    return get_marjority_class(sv);
}

void KNN::fit(vec_of_str_db_vec_map x) {
  points = x;
}

int KNN::predict(vec_of_str_db_vec_map x) {
  int correct {0};
  for (const unordered_map<string, vector<double>>& dict : x) {
    for (const auto& it : dict) {
      y_pred = it.first;
      y_hat = classify_point(it.second);
      if (y_hat == y_pred) {
        correct++;
        }
    }
  }
  return correct;
}
double KNN::cosine_similarity(vector<double> *A, vector<double> *B, unsigned int Vector_Length)
{
    double dot = 0.0, denom_a = 0.0, denom_b = 0.0 ;
     for(unsigned int i = 0u; i < Vector_Length; ++i) {
        dot += A[i] * B[i] ;
        denom_a += A[i] * A[i] ;
        denom_b += B[i] * B[i] ;
    }
    return dot / (std::sqrt(denom_a) * std::sqrt(denom_b));
}
/*
with open(Path(BASE_DIR / DATA_PATH / "stopwords_en.txt"), 'r') as file:
    stopwords: list = [file.read().replace('\n', ',')]
 

path_to_data: Path = BASE_DIR / DATA_PATH / "emails" / "email.csv"
dataset = build_dataset(path_to_data)
clean = clean_dataset(dataset[:200])
encoded_data = get_tf_idf(clean)
# Train test split
train_data, test_data = train_test_split(encoded_data, 0.8)
*/

