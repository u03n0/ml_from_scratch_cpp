#ifndef KNN_H
#define KNN_H
#include <string>
#include <vector>
#include <unordered_map>

using std::vector;
using std::string;
using std::unordered_map;


// A class to represent a basic KNN model

class KNN {
public:
  int k;
  vector<vector<double>> points;
  vector<string> labels;
  // Constructor
  KNN(int k=3);
  
  // Training method
  void fit(vector<vector<double>> X, vector<string> y);
    
  // Prediction method
  int predict(vector<vector<double>> X, vector<string> y); 

  // classify 
  string classify_point(vector<double> x);

  double cosine_similarity(vector<double> A, vector<double> B);

  string get_marjority_class(vector<std::pair<double, string>> x);

};

#endif // KNN_H
