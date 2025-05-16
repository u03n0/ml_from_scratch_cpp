#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <random>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <sstream>

using std::vector;
using std::string;
using std::unordered_map;
using vec_of_vec_str_map = vector<unordered_map<string, vector<string>>>;

double compute_product(vector<string> text, 
                      unordered_map<string, int> histogram, 
                      int num_words, 
                      double proba, 
                      int alpha = 1) {
  double product = 1.0;
  for (const string& word: text) {
    if (histogram.find(word) != histogram.end()) {
      product *= (static_cast<double>(histogram.at(word)) + alpha) / num_words;
    } else {
      product *= static_cast<double>(alpha) / num_words;
    }
  }
  return product * proba;
}



int vocabulary_counter(unordered_map<string, int> data) {
  int sum {0};
  for (const auto& pair : data) {
    sum += pair.second;
  }
  return sum;
}

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


unordered_map<string, int> build_histogram(vector<unordered_map<string, vector<string>>> data) {
  unordered_map<string, int> histogram_map;
  for (unordered_map<string, vector<string>> dict : data) {
    for (const auto& entry : dict) {
      const vector<string>& value = entry.second;
      for (const auto& word : value) {
        histogram_map[remove_punctuation(lower_str(word))]++;
      }
    }
  }
  return histogram_map;
}


std::pair<vec_of_vec_str_map, vec_of_vec_str_map> train_test_split(vec_of_vec_str_map data, double ratio) {
  std::random_device rd;  // Get a random seed from the hardware (if available)
  std::default_random_engine rng(rd());  // Default random engine seeded with random_device
  std::shuffle(data.begin(), data.end(), rng);
  double split_index  {ratio * data.size()};
  vec_of_vec_str_map train_data {data.begin(), data.begin() + (int) split_index};
  vec_of_vec_str_map test_data {data.begin() + (int) split_index, data.end()};
  return std::make_pair(train_data, test_data);
}


vector<string> split(string &s, char delim) {
  vector<string> result;
  std::stringstream ss (s);
  string item;

  while (getline (ss, item, delim)) {
    result.push_back (item);
  }
  return result;
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


vec_of_vec_str_map parseCSV(const string& filename) {
    // Open the CSV file
    std::ifstream file(filename);
    
    // Check if the file was opened successfully
    if (!file.is_open()) {
        std::cerr << "Could not open the file!" << std::endl;
        exit(1); // Exit if the file can't be opened
    }
    
    // Vector to store unordered_maps
    vec_of_vec_str_map data;
    
    string line;
    
    // Read each line from the CSV file
    while (getline(file, line)) {
        string category, message;
        
        // Find the position of the comma separating Category and Message
        size_t comma_pos = line.find(",");
        
        if (comma_pos != string::npos) {
            category = line.substr(0, comma_pos);
            message = line.substr(comma_pos + 1); // Everything after the comma
            
            // Remove leading/trailing whitespaces in category (optional)
            size_t start = category.find_first_not_of(" \t");
            size_t end = category.find_last_not_of(" \t");
            category = category.substr(start, end - start + 1);
            
            // Remove leading/trailing whitespaces in message (optional)
            start = message.find_first_not_of(" \t");
            end = message.find_last_not_of(" \t");
            message = message.substr(start, end - start + 1);
            
            // Split message into words
            vector<string> words;
            std::stringstream ss(message);
            string word;
            
            while (ss >> word) {
                // Clean the word: remove punctuation, remove numbers, and convert to lowercase
                word = cleanWord(word);

                // Add the word to the list if it's not empty
                if (!word.empty()) {
                    words.push_back(word);
                }
            }
            
            // Create a new unordered_map for the category and its associated words
            unordered_map<string, vector<string>> category_map;
            category_map[category] = words;
            
            // Add the unordered_map to the vector
            data.push_back(category_map);
        }
    }
    
    // Close the file
    file.close();
    
    return data;
}
