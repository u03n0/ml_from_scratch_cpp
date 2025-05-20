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


double tf(string term, unordered_map<string, vector<string>> document); 
double idf(string term, vector<unordered_map<string, vector<string>>> corpus); 
set<string> get_vocab( vector<unordered_map<string, vector<string>>> corpus);
vector<unordered_map<string, vector<double>>> get_tf_idf(vector<unordered_map<string, vector<string>>> corpus); 
#endif // !TEXT_TERMS_H

