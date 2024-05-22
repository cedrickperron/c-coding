#ifndef FILTER_DATA_POINTS_H
#define FILTER_DATA_POINTS_H

#include <vector>
#include <rarray>

std::vector<double> filter_data_points(const rarray<double, 1>& dataPoints, int rank, int size);

#endif
