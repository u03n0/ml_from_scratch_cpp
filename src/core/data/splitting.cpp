#include <vector>
#include <unordered_map>
#include <random>
#include <sstream>
#include <algorithm>


using std::vector;
using std::unordered_map;
using std::string;
using vec_of_vec_str_map = vector<unordered_map<string, vector<string>>>;


std::pair<vec_of_vec_str_map, vec_of_vec_str_map> train_test_split(vec_of_vec_str_map data,
                                                                  double ratio) {
  std::random_device rd;
  std::default_random_engine rng(rd());
  std::shuffle(data.begin(), data.end(),  rng);
  double split_index {ratio * data.size()};
  vec_of_vec_str_map train_data {data.begin(), data.begin() + (int) split_index};
  vec_of_vec_str_map test_data {data.begin() + (int) split_index, data.end()};
  return std::make_pair(train_data, test_data);
}

vector<string> split(string &s, char delim) {
  vector<string> result;
  std::stringstream ss (s);
  string item;

  while (getline (ss, item, delim)) {
    result.push_back(item);
  }
  return result;
}
