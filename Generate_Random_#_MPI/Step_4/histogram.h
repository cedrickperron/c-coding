#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <rarray>
#include <vector>
#include <iostream>

void print_normalized_histogram(const rarray<int, 1>& histogram, double dx, unsigned long long N);
rarray<int, 1> compute_histogram(const std::vector<double>& data_points, double dx);
void add_to_global_hist(rarray<int, 1>& global_histogram, const rarray<int, 1>& histogram);

#endif
