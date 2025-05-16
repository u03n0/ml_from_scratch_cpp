#ifndef PROCESSING_H
#define PROCESSING_H
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using std::string;
using std::vector;
using std::unordered_map;
using vec_of_vec_str_map = vector<unordered_map<string, vector<string>>>;


// Data functions
string lower_str(string str);
string removePunctuation(const string& word);

// Helper functions
unordered_map<string, int> build_histogram(vector<unordered_map<string, vector<string>>> data);
int vocabulary_counter(unordered_map<string, int> data);
double compute_product(vector<string> words, unordered_map<string, int> dict, int num_words, double proba, int alpha);
// CSV Parsing
vec_of_vec_str_map parseCSV(const string& filename);
std::pair<vec_of_vec_str_map, vec_of_vec_str_map> train_test_split(vec_of_vec_str_map data, double ratio); 
#endif
