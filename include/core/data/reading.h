#ifndef READING_H
#define READING_H
#include <vector>
#include <string>
#include <unordered_map>

//#include "ml_from_scratch_cpp/core/data/text.h"
using std::vector;
using std::string;
using std::unordered_map;

typedef vector<unordered_map<string, string>> str_omap_vector_t;
/**
 * Parses a CSV file 
 * @param filename The full path name of the csv file
 * @return a vector of maps (string vector<string>)
*/
 vector<vector<string>> read_csv(const string& filename);
void display_csv(const vector<vector<string>>& data);
#endif // READING_H
