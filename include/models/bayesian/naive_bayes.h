#ifndef NAIVE_BAYES_H
#define NAIVE_BAYES_H
#include <string>
#include <vector>
#include <unordered_map>

using std::string;
using std::vector;
using std::unordered_map;
typedef vector<unordered_map<string, vector<string>>> dataset_vec_str_t;


class NaiveBayes {
public:
    double ham_proba, spam_proba, product_ham, product_spam;
    int num_ham_words, num_spam_words, len_ham, correct, alpha;
    vector<vector<string>> ham_data, spam_data;
    unordered_map<string, int> ham_histogram, spam_histogram;
    vector<string> y_hat, y;
    
    // Constructor
    NaiveBayes(int a=1);
    
    // Training method
    void fit(vector<vector<string>> X, vector<string> y);
    
    // Prediction method
    int predict(vector<vector<string>> X, vector<string> y); 

    // Product computer method
    double compute_product(vector<string> x,
        unordered_map<string, int> y,
        int z,
        double p,
        int a);

    // Vocabulary counter method
    int vocabulary_counter(unordered_map<string, int> x);

    // Histogram builder method
    unordered_map<string, int> build_histogram(vector<vector<string>> X);
};

#endif // NAIVE_BAYES_H
