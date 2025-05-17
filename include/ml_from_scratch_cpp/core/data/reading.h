#ifndef READING_H
#define READING_H
#include <vector>
#include <string>
#include <unordered_map>

//#include "ml_from_scratch_cpp/core/data/text.h"
using std::vector;
using std::string;
using std::unordered_map;
using vec_of_str_map = vector<unordered_map<string, string>>;


/**
 * Parses a CSV file 
 * @param filename The full path name of the csv file
 * @return a vector of maps (string vector<string>)
*/
vec_of_str_map read_csv(const string& filename);

#endif // READING_H
