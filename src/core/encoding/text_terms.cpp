#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <cmath>
#include <set>
#include "core/encoding/text_terms.h"

using std::vector;
using std::unordered_map;
using std::string;
using std::set;


vector<vector<double>> tf_idf(vector<vector<string>> data) {
  // build vocabulary and get histograms for each document
  set<string> vocab;
  unordered_map<string, int> idfs;
  vector<unordered_map<string, int>> corpus_histo;
  

  for (const vector<string>& sub : data) {
    unordered_map<string, int> doc_histo;
    for (const string& term : sub) {
      vocab.insert(term);
      doc_histo[term]++;
    }
    corpus_histo.push_back(doc_histo);
  }

  //  Initialize a Matrix with zeros
  size_t len_data = data.size();
  size_t len_vocab = vocab.size();

  vector<vector<double>> matrix(len_data, vector<double>(len_vocab, 0.0));

  // Build IDFs now
  for (string term: vocab) {
    for (const unordered_map<string, int>& d_histo : corpus_histo) {
      if (d_histo.find(term) != d_histo.end()) {
        idfs[term]++;
      }
    }
  }

  vector<string> vocab_vec(vocab.begin(), vocab.end()); // convert set to vector
  
  // Populate Matrix with TF * IDF product
  for (size_t i = 0; i < corpus_histo.size(); i++) {
    size_t doc_length = data[i].size();
    for (size_t j = 0; j < vocab_vec.size(); j++) {
      string term = vocab_vec[j];
      int x = 0;
      auto it = corpus_histo[i].find(term);
      if (it != corpus_histo[i].end()) {
        x = it->second;
      }
      double idf = log(static_cast<double>(len_data) / idfs[term]);
      double term_freq = static_cast<double>(x) / doc_length;
      matrix[i][j] = idf * term_freq;
    }
  }
  return matrix;
}
