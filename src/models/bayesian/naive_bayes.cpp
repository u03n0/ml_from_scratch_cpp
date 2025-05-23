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
    
    void NaiveBayes::fit(vector<vector<string>> X) {
      train_data = x;
      for (const auto& dict : train_data) {
        if (dict.find("ham") != dict.end()) {
          len_ham++;
          ham_data.push_back({{"ham", dict.at("ham")}});
        }
        if (dict.find("spam") != dict.end()) {
          spam_data.push_back({{"spam", dict.at("spam")}});
        }
      }
      ham_proba = static_cast<double>(len_ham) / train_data.size();
      spam_proba  = 1.0 - ham_proba;
      ham_histogram = build_histogram(ham_data);
      spam_histogram = build_histogram(spam_data);
      num_ham_words = vocabulary_counter(ham_histogram);
      num_spam_words = vocabulary_counter(spam_histogram);
    }

    int NaiveBayes::predict(dataset_vec_str_t x) { 
      test_data = x;
      for (const auto& email : test_data) {
        for (const auto& pair : email) {
          y.push_back(pair.first);
          product_ham = compute_product(pair.second, ham_histogram, num_ham_words, ham_proba, alpha);
          product_spam = compute_product(pair.second, spam_histogram, num_spam_words, spam_proba, alpha);
          y_hat.push_back(product_spam > product_ham ? "spam" : "ham");
        }
      }
      for (size_t i {0}; i < y_hat.size(); i++) {
        if (y_hat[i] == y[i]) {
          correct++;
        }
      }
      return correct;
    }
    
    unordered_map<string, int> NaiveBayes::build_histogram(dataset_vec_str_t x) {
      dataset_vec_str_t data {x};
      unordered_map<string, int> histogram_map;
      for (unordered_map<string, vector<string>> dict : data) {
        for (const auto& entry : dict) {
          const vector<string>& value = entry.second;
          for (const auto& word : value) {
            histogram_map[word]++;
          }
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
