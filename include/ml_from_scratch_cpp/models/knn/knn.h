#ifndef KNN_H
#define KNN_H
#include <string>
#include <vector>
#include <unordered_map>

using std::string;
using std::vector;
using std::unordered_map;
using vec_of_str_db_vec_map = vector<unordered_map<string, vector<double>>>;

class KNN {
public:
  int k;
  vec_of_str_db_vec_map points;
  // Constructor
  KNN(int k=3);
  
  // Training method
  void fit(vec_of_str_db_vec_map x);
    
  // Prediction method
  int predict(vec_of_str_db_vec_map x); 

  // classify 
  string classify_point(vector<double> x);

  double cosine_similarity(vector<double> *A, vector<double> *B, unsigned int Vector_Length);

  string get_marjority_class(vector<unordered_map<double, string>> x);

};

#endif // KNN_H
