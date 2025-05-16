#ifndef NAIVE_BAYES_H
#define NAIVE_BAYES_H
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
    unordered_map<string, int> ham_histogram, spam_histogram;
    vector<string> y_hat, y;
    
    // Constructor
    NaiveBayes(int a=1);
    
    // Training method
    void fit(vec_of_vec_str_map x);
    
    // Prediction method
    int predict(vec_of_vec_str_map x); 

    // Product computer method
    double compute_product(vector<string> x,
        unordered_map<string, int> y,
        int z,
        double p,
        int a);

    // Vocabulary counter method
    int vocabulary_counter(unordered_map<string, int> x);

    // Histogram builder method
    unordered_map<string, int> build_histogram(vec_of_vec_str_map x);
};

#endif // NAIVE_BAYES_H
