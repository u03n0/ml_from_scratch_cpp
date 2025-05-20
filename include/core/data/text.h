#ifndef TEXT_H
#define TEXT_H
#include <string>
#include <unordered_map>
#include <vector>

using std::string;
using std::unordered_map;
using std::vector;

// Text (string) related functions
string lower_str(string str);
string remove_punctuation(const string& word);
string cleanWord(const string& word);
vector<unordered_map<string, vector<string>>> tokenize_dataset(const vector<unordered_map<string, string>> data);

#endif // TEXT_H
