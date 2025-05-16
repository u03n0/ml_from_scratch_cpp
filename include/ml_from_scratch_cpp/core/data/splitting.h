#ifndef SPLITTING_H
#define SPLITTING_H
#include <vector>
#include <unordered_map>
#include <string>


using std::vector;
using std::unordered_map;
using std::string;
using vec_of_vec_str_map = vector<unordered_map<string, vector<string>>>;

// Train-test split of a dataset
std::pair<vec_of_vec_str_map, vec_of_vec_str_map> train_test_split(vec_of_vec_str_map data,
                                                                  double ratio);
// Splits text on a deliminator
vector<string> split(string &s, char delim);
#endif
