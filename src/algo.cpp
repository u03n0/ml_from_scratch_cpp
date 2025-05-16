#include <vector>
#include <unordered_map>
#include "../include/processing.h"
#include "../include/algo.h"

NaiveBayes::NaiveBayes(int a) {
      alpha = a;
      len_ham = 0;
      correct = 0;
    }
    
    void NaiveBayes::fit(vec_of_vec_str_map x) {
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

    int NaiveBayes::predict(vec_of_vec_str_map x) { 
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
