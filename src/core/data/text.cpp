#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "ml_from_scratch_cpp/core/data/text.h"
#include "ml_from_scratch_cpp/core/data/reading.h"


using std::vector;
using std::string;
using std::unordered_map;
using vec_of_vec_str_map = vector<unordered_map<string, vector<string>>>;


string lower_str(string str) {
  string lowered {""};
  for (char c: str) {
    lowered += tolower(c);
  }
  return lowered;
}

string remove_punctuation(const string& word) {
  string cleaned_word {word};
  cleaned_word.erase(cleaned_word.begin(),
      std::find_if(cleaned_word.begin(), 
        cleaned_word.end(), 
        [](unsigned char ch){
        return std::isalnum(ch);
        })
  );
  cleaned_word.erase(
      std::find_if(cleaned_word.rbegin(),
        cleaned_word.rend(),
        [](unsigned char ch){
        return std::isalnum(ch);
        }).base(),
      cleaned_word.end()
      );
  return cleaned_word;
}

string cleanWord(const string& word) {
    string cleanedWord;

    // Iterate over each character in the word
    for (char ch : word) {
        // Keep only alphabetic characters
        if (std::isalpha(static_cast<unsigned char>(ch))) {
            // Convert to lowercase and add to the result
            cleanedWord += std::tolower(static_cast<unsigned char>(ch));
        }
    }
    return cleanedWord;
}
