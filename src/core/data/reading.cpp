#include <vector>
#include <string>
#include <filesystem>
#include <fstream>
#include <unordered_map>
#include <tuple>
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


str_omap_vector_t read_csv(const string& filename) {
  str_omap_vector_t data;
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Failed to open file: " << filename << std::endl;
    return data;
  }

  string line;
  while (std::getline(file, line)) {
    vector<string> sentence = parse_csv_row(line);
    unordered_map<string, string> dict;
    dict[sentence.front()] = sentence.back(); 
    data.push_back(dict);
  }

  file.close();
  return data;
}
