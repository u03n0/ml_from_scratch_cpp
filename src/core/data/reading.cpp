#include <vector>
#include <string>
#include <filesystem>
#include <fstream>
#include <unordered_map>
#include <iostream>
#include "ml_from_scratch_cpp/core/data/text.h"


using std::vector;
using std::string;
using std::unordered_map;
using vec_of_vec_str_map = vector<unordered_map<string, vector<string>>>;



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
