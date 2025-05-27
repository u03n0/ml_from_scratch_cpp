#ifndef LR_H
#define LR_H

#include <vector>
#include <string>
#include <unordered_map>

using std::vector;
using std::string;
using std::unordered_map;
typedef vector<unordered_map<string, vector<double>>> dataset_vec_double_t;


class LinearRegression {
public:
    double lr;
    int num_iters;
    vector<double> weights;
    double bias;

    LinearRegression(double x=0.001,int y=400);
    void fit(vector<vector<double>>& X, vector<double>& y);
    // Helper function to convert your dataset format to X and y
    //void extractFeaturesAndLabels(const dataset_vec_double_t& dataset, 
                                 // vector<vector<double>>& X, 
                                  //vector<double>& y); 
    vector<double> predict(const vector<vector<double>>& X);
};

#endif // !LR_H

