#ifndef KNN_H
#define KNN_H
#include <string>
#include <vector>
#include <unordered_map>

using std::vector;
using std::string;
using std::unordered_map;

typedef vector<unordered_map<string, vector<double>>> str_db_pairList_t;

// A class to represent a basic KNN model

class KNN {
public:
  int k;
  str_db_pairList_t points;
  // Constructor
  KNN(int k=3);
  
  // Training method
  void fit(str_db_pairList_t x);
    
  // Prediction method
  int predict(str_db_pairList_t x); 

  // classify 
  string classify_point(vector<double> x);

  double cosine_similarity(vector<double> A, vector<double> B);

  string get_marjority_class(vector<std::pair<double, string>> x);

};

#endif // KNN_H
