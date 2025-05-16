#ifndef TEXT_H
#define TEXT_H
#include <string>
#include <unordered_map>

using std::string;
using std::unordered_map;

// Text (string) related functions
string lower_str(string str);
string remove_punctuation(const string& word);
string cleanWord(const string& word);

#endif // TEXT_H
