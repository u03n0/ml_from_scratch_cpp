#include "models/linear/lr.h"
#include <vector>
#include <string>
#include <unordered_map>

using std::vector;
using std::string;
using std::unordered_map;

typedef vector<unordered_map<string, vector<double>>> dataset_vec_double_t;

LinearRegression::LinearRegression(double x, int y)
  : lr(x), num_iters(y), bias(0.0) {}

void LinearRegression::extractFeaturesAndLabels(const dataset_vec_double_t& dataset, 
                                  vector<vector<double>>& X, 
                                  vector<double>& y) {
        X.clear();
        y.clear();
        
        for (const auto& sample : dataset) {
            for (const auto& [label, features] : sample) {
                X.push_back(features);
                
                // Convert label to numeric
                // Assuming binary classification: "spam" = 1.0, "ham" = 0.0
                double label_value = (label == "spam") ? 1.0 : 0.0;
                y.push_back(label_value);
            }
        }
    }
void LinearRegression::fit(dataset_vec_double_t& dataset){
  vector<vector<double>> X;
  vector<double> y;
  // Convert dataset to X (features) and y (labels)
  extractFeaturesAndLabels(dataset, X, y);
  size_t num_samples = X.size();
  size_t num_features = X[0].size();
  // Initialize weights to zero
  weights = vector<double>(num_features, 0.0);
  // Pre-allocate vectors for predictions and errors
  vector<double> y_pred(num_samples);
  vector<double> errors(num_samples);
  vector<double> weights_grad(num_features);
    
  for (int iter = 0; iter < num_iters; iter++) {
    // Compute predictions
    for (size_t i = 0; i < num_samples; i++) {
      y_pred[i] = bias;
      for (size_t j = 0; j < num_features; j++) {
          y_pred[i] += X[i][j] * weights[j];
      }
      // Store errors immediately
      errors[i] = y_pred[i] - y[i];
    }
    // Compute weight gradients using pre-calculated errors
    fill(weights_grad.begin(), weights_grad.end(), 0.0);
    for (size_t j = 0; j < num_features; j++) {
      for (size_t i = 0; i < num_samples; i++) {
        weights_grad[j] += X[i][j] * errors[i];
      }
      weights_grad[j] /= num_samples;
    }
    // Compute bias gradient
    double bias_grad = 0.0;
    for (double error : errors) {
      bias_grad += error;
      }
    bias_grad /= num_samples;
      // Update weights and bias
    for (size_t j = 0; j < num_features; j++) {
        weights[j] -= lr * weights_grad[j];
      }
        bias -= lr * bias_grad;
    }
}
vector<double> LinearRegression::predict(const vector<vector<double>>&  X) {
    vector<double> predictions;
    predictions.reserve(X.size());
    
    for (const auto& sample : X) {
        double prediction = bias;
        
        // Calculate dot product of sample and weights
        for (size_t i = 0; i < sample.size(); i++) {
            prediction += sample[i] * weights[i];
        }
        
        predictions.push_back(prediction);
    }
    
    return predictions;
}
