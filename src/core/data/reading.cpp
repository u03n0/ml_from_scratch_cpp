#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
#include <iostream>
#include "core/data/text.h"


using std::vector;
using std::string;
using std::unordered_map;

typedef vector<unordered_map<string, string>> str_omap_vector_t;

vector<string> parse_csv_row(const string& row) {
  vector<string> fields;
  string field;
    bool inQuotes = false;
    
    for (char c : row) {
      if (!inQuotes && c == ',') {
        fields.push_back(field);
        field.clear();
      } else if (c == '"') {
        inQuotes = !inQuotes;
      } else {
        field += c;
      }
    }
    fields.push_back(field);
    
    return fields;
}

vector<vector<string>> read_csv(const string& filename) {
    std::ifstream file(filename); // Open the file
    string line;
    vector<vector<string>> data; // To store rows of the CSV file

    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return data; // Return empty vector on error
    }

    // Loop through each row in the CSV file
    while (std::getline(file, line)) {
        vector<string> row = parse_csv_row(line);
        data.push_back(row);
    }

    file.close(); // Close the file
    data.pop_back();
    return data; // Return the 2D vector containing all rows and columns
}


void display_csv(const vector<vector<string>>& data) {
    for (const auto& row : data) {
        for (const auto& column : row) {
            std::cout << column << " ";
        }
        std::cout << std::endl;
    }
}
