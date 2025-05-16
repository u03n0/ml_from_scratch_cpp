#ifndef ALGO_H
#define ALGO_H
#include <string>
#include <vector>
#include <unordered_map>

using std::string;
using std::vector;
using std::unordered_map;
using vec_of_vec_str_map = vector<unordered_map<string, vector<string>>>;


class NaiveBayes {
public:
    double ham_proba, spam_proba, product_ham, product_spam;
    int num_ham_words, num_spam_words, len_ham, correct, alpha;
    vec_of_vec_str_map ham_data, spam_data, train_data, test_data;
    std::unordered_map<std::string, int> ham_histogram, spam_histogram;
    std::vector<std::string> y_hat, y;
    
    // Constructor
    NaiveBayes(int a=1);
    
    // Training method
    void fit(vec_of_vec_str_map x);
    
    // Prediction method
    int predict(vec_of_vec_str_map x); 
};

#endif // NAIVE_BAYES_H
