#ifndef SPLITTING_H
#define SPLITTING_H
#include <utility>
#include <random>
#include <algorithm>

template<typename T>
std::pair<T, T> train_test_split(T data, double ratio) {
  std::random_device rd;
  std::default_random_engine rng(rd());
  std::shuffle(data.begin(), data.end(), rng);
  size_t split_index = static_cast<size_t>(ratio * data.size());
  T train_data(data.begin(), data.begin() + split_index);
  T test_data(data.begin() + split_index, data.end());
  return std::make_pair(train_data, test_data);
}
// Splits text on a deliminator
vector<string> split(string &s, char delim);
#endif
