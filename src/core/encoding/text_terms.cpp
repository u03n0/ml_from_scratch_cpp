#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <cmath>
#include <set>

using std::vector;
using std::unordered_map;
using std::string;
using std::set;

// Optimized TF-IDF implementation
vector<vector<double>> get_tf_idf_optimized(const vector<vector<string>>& corpus) {
    if (corpus.empty()) return {};
    
    // Build vocabulary and document frequency in one pass
    set<string> vocab_set;
    unordered_map<string, int> doc_freq; // How many documents contain each term
    
    for (const auto& doc : corpus) {
        set<string> unique_terms(doc.begin(), doc.end()); // Unique terms in this doc
        for (const auto& term : unique_terms) {
            vocab_set.insert(term);
            doc_freq[term]++;
        }
    }
    
    vector<string> vocab(vocab_set.begin(), vocab_set.end());
    int vocab_size = vocab.size();
    int num_docs = corpus.size();
    
    // Pre-compute IDF values
    unordered_map<string, double> idf_values;
    for (const auto& term : vocab) {
        if (doc_freq[term] > 0) {
            idf_values[term] = std::log(static_cast<double>(num_docs) / doc_freq[term]);
        } else {
            idf_values[term] = 0.0;
        }
    }
    
    // Create TF-IDF vectors
    vector<vector<double>> tfidf_matrix;
    tfidf_matrix.reserve(num_docs);
    
    for (const auto& doc : corpus) {
        // Count term frequencies in this document
        unordered_map<string, int> term_count;
        for (const auto& term : doc) {
            term_count[term]++;
        }
        
        // Create TF-IDF vector for this document
        vector<double> tfidf_vec(vocab_size, 0.0);
        int doc_length = doc.size();
        
        if (doc_length > 0) {
            for (int i = 0; i < vocab_size; ++i) {
                const string& term = vocab[i];
                if (term_count.count(term)) {
                    double tf = static_cast<double>(term_count[term]) / doc_length;
                    tfidf_vec[i] = tf * idf_values[term];
                }
            }
        }
        
        tfidf_matrix.push_back(std::move(tfidf_vec));
    }
    
    return tfidf_matrix;
}

// Alternative: Simpler bag-of-words for faster processing
vector<vector<double>> get_bag_of_words(const vector<vector<string>>& corpus) {
    if (corpus.empty()) return {};
    
    // Build vocabulary
    set<string> vocab_set;
    for (const auto& doc : corpus) {
        for (const auto& term : doc) {
            vocab_set.insert(term);
        }
    }
    
    vector<string> vocab(vocab_set.begin(), vocab_set.end());
    int vocab_size = vocab.size();
    
    // Create feature vectors
    vector<vector<double>> feature_matrix;
    feature_matrix.reserve(corpus.size());
    
    for (const auto& doc : corpus) {
        unordered_map<string, int> term_count;
        for (const auto& term : doc) {
            term_count[term]++;
        }
        
        vector<double> feature_vec(vocab_size, 0.0);
        for (int i = 0; i < vocab_size; ++i) {
            const string& term = vocab[i];
            if (term_count.count(term)) {
                feature_vec[i] = static_cast<double>(term_count[term]);
            }
        }
        
        feature_matrix.push_back(std::move(feature_vec));
    }
    
    return feature_matrix;
}
