//#include <vector>
//#include <string>
//#include <unordered_map>
#include <cmath>
#include <algorithm>
#include "models/knn/knn.h"


KNN::KNN(int x) {  
  k = x;
}
  string KNN::get_marjority_class(vector<std::pair<double, string>> distances) {
    
    unordered_map<string, int> result; // store class label (string) and count (int)
    
    for (const std::pair<double, string>& p : distances) {
        if (result.find(p.second) == result.end()) {
            result[p.second] = 1;
          } else {
            result[p.second]++;
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
    vector<std::pair<double, string>> distances;
    for (const unordered_map<string , vector<double>>& dict : points) {
        for (const auto& it : dict) {
            //double dist = cosine_similarity(point, it.second, point.size());
            double dist = 43.3;
            std::pair<double, string> p (dist, it.first);
            distances.push_back(p);
          }
    }
    std::sort(distances.begin(), distances.end(), [](auto& a, auto& b){return a.first > b.first;});
    vector<std::pair<double, string>> sv(distances.begin(), distances.begin() + k);
    return get_marjority_class(sv);
}

void KNN::fit(str_db_pairList_t x) {
  points = x;
}

int KNN::predict(str_db_pairList_t x) {
  int correct {0};
  for (const unordered_map<string, vector<double>>& dict : x) {
    for (const auto& it : dict) {
      string y_pred = it.first;
      string y_hat = classify_point(it.second);
      if (y_hat == y_pred) {
        correct++;
        }
    }
  }
  return correct;
}
double KNN::cosine_similarity(vector<double> A, vector<double> B)
{
    double dot = 0.0, denom_a = 0.0, denom_b = 0.0 ;
     for(size_t i=0; i < A.size(); ++i) {
        dot += A[i] * B[i] ;
        denom_a += A[i] * A[i] ;
        denom_b += B[i] * B[i] ;
    }
    return dot / (std::sqrt(denom_a) * std::sqrt(denom_b));
}
