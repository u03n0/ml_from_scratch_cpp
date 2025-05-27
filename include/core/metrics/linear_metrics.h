#ifndef LINEAR_METRICS_H
#define LINEAR_METRICS_H
#include <vector>

using std::vector;


double calculate_mae(const std::vector<double>& y_true, const std::vector<double>& y_pred);
double calculate_r2(const std::vector<double>& y_true, const std::vector<double>& y_pred);

double calculate_rmse(const vector<double>& y_true, const vector<double>& y_pred);
#endif // !LINEAR_METRICS_H




