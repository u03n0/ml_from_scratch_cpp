#include <vector>
#include <unordered_map>
#include <string>
#include "models/bayesian/naive_bayes.h"
#include "core/data/text.h"


NaiveBayes::NaiveBayes(int a) {
      alpha = a;
      len_ham = 0;
      correct = 0;
      
    }
    
    void NaiveBayes::fit(vector<vector<string>> X, vector<string> y) {
      size_t num_rows = X.size();
      for (size_t i = 0; i < num_rows; i++) {
        if (y[i] == "ham") {
          len_ham++;
          ham_data.push_back(X[i]);
        }else {
          spam_data.push_back(X[i]);
        }
      }

      ham_proba = static_cast<double>(len_ham) / num_rows;
      spam_proba  = 1.0 - ham_proba;
      ham_histogram = build_histogram(ham_data);
      spam_histogram = build_histogram(spam_data);
      num_ham_words = vocabulary_counter(ham_histogram);
      num_spam_words = vocabulary_counter(spam_histogram);
    }

    int NaiveBayes::predict(vector<vector<string>> X, vector<string> y) { 

      for (size_t i = 0; i < X.size(); i++) {
        vector<string> row = X[i];
        product_ham = compute_product(row, ham_histogram, num_ham_words, ham_proba, alpha);
        product_spam = compute_product(row, spam_histogram, num_spam_words, spam_proba, alpha);
        y_hat.push_back(product_spam > product_ham ? "spam" : "ham");
      }
      for (size_t i {0}; i < y_hat.size(); i++) {
        if (y_hat[i] == y[i]) {
          correct++;
        }
      }
      return correct;
    }
    
    unordered_map<string, int> NaiveBayes::build_histogram(vector<vector<string>> X) {
    
      unordered_map<string, int> histogram_map;
      for (vector<string>& row : X) {
        for (const auto& word : row) {
            histogram_map[word]++;
          }
        }
  return histogram_map;
}
    int NaiveBayes::vocabulary_counter(unordered_map<string, int> x) {
      unordered_map<string, int> data {x};
      int sum {0};
      for (const auto& pair : data) {
        sum += pair.second;
      }
      return sum;
    }

    double NaiveBayes::compute_product(vector<string> x, 
                      unordered_map<string, int> y, 
                      int z, 
                      double p, 
                      int a = 1) {
      vector<string> text {x};
      unordered_map<string, int> histogram {y};
      int num_words {z};
      double proba {p};
      int alpha {a};
    double product = 1.0;
    for (const string& word: text) {
      if (histogram.find(word) != histogram.end()) {
        product *= (static_cast<double>(histogram.at(word)) + alpha) / num_words;
      } else {
        product *= static_cast<double>(alpha) / num_words;
      }
    }
    return product * proba;
  }
