//#include <vector>
//#include <string>
//#include <unordered_map>
#include <cmath>
#include <algorithm>
#include "models/knn/knn.h"
#include <queue>

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
    // Min-heap to keep top-k similarities
    std::priority_queue<std::pair<double, string>, 
                       vector<std::pair<double, string>>, 
                       std::greater<std::pair<double, string>>> top_k;
    
    for (size_t i = 0; i < points.size(); i++) {
        double sim = cosine_similarity(point, points[i]);
        
        if (top_k.size() < k) {
            top_k.push({sim, labels[i]});
        } else if (sim > top_k.top().first) {
            top_k.pop();
            top_k.push({sim, labels[i]});
        }
    }
    
    // Convert to vector for majority class calculation
    vector<std::pair<double, string>> top_similarities;
    while (!top_k.empty()) {
        top_similarities.push_back(top_k.top());
        top_k.pop();
    }
    
    return get_marjority_class(top_similarities);
}

void KNN::fit(vector<vector<double>> X, vector<string> y) {
  points = X;
  labels = y;
}

  int KNN::predict(vector<vector<double>> X, vector<string> y) {
  int correct {0};
  for (size_t i = 0; i < X.size(); i++) {
    string y_pred = y[i];
    string y_hat = classify_point(X[i]);
      if (y_hat == y_pred) {
        correct++;
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
