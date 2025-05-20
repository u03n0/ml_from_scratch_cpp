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


double tf(string term, vector<string> document) {
  int n = document.size();
  int freq {0};
  for (const string& word : document) {
      if (word == term){
        freq++;
      }
    }
    return freq / n ? n : 0;
}


double idf(string term, vector<unordered_map<string, vector<string>>> corpus) {
  int n = corpus.size();
  int count {0};   
  for (const unordered_map<string, vector<string>>& doc : corpus) {
    for (const auto& pair : doc) {
      if (std::find(pair.second.begin(), pair.second.end(), term) == pair.second.end()) {
        count++;
        break;
      }
    }
  }
  
    if (count == 0) {
           return 0;
    }

    return std::log((n + 1) / (count + 1)) + 1;
    }

set<string> get_vocab(vector<unordered_map<string, vector<string>>> corpus) {
  set<string> vocab;
    for (const unordered_map<string, vector<string>>& doc : corpus) {
         for (const auto& pair : doc) {
            for (const string& term : pair.second) {
                vocab.insert(term);
            }
         }
    }
    return vocab;
}


vector<unordered_map<string, vector<double>>> get_tf_idf(vector<unordered_map<string, vector<string>>> corpus) {

  set<string> vocab_set = get_vocab(corpus); // a set of all terms in corpus (a vocabulary)
  vector<string> vocab(vocab_set.begin(), vocab_set.end()); // converted to a vector
  int vocab_len = vocab.size(); // used to build a vector of 0s
  unordered_map<string , double> term_idfs; // track the idf for all terms in vocab
  for (const string& term : vocab) {
    term_idfs[term] = idf(term, corpus); // store the term and its idf
  }
  // second part
  vector<unordered_map<string, vector<double>>> results;
  for (const unordered_map<string, vector<string>>& doc : corpus) { // for every doc in corpus
    unordered_map<string, int> term_freq; // to store tf 
    vector<double> vec(vocab_len, 0.0); // a vector intialized to 0 * length of vocab
    for (const auto& pair : doc){ // for every key, value pair in each document
      string label = pair.first; // our label is the key
      for (const string& term : pair.second) {
        term_freq[term] = tf(term, pair.second); // store term and its tf for that document
    }
    
    for (int i = 0; i < vocab_len; i++){
      string term = vocab[i]; // get the ith term in the vocab
      vec[i] = term_freq[term] * term_idfs[term]; // update ith item in vector with the tf-idf of the ith term
    }
    unordered_map<string, vector<double>> res;
    res[label] = vec;
    results.push_back(res);
  }
  }
    return results;
  }
