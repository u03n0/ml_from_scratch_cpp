#ifndef TEXT_TERMS_H
#define TEXT_TERMS_H

#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <set>

using std::string;
using std::unordered_map;
using std::vector;
using std::set;


set<string> get_vocab( vector<unordered_map<string, vector<string>>> corpus);
vector<vector<double>> get_tf_idf_optimized(const vector<vector<string>>& corpus);
vector<vector<double>> get_bag_of_words(const vector<vector<string>>& corpus);
#endif // !TEXT_TERMS_H

