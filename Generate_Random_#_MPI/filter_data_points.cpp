#include "filter_data_points.h"

std::vector<double> filter_data_points(const rarray<double, 1>& dataPoints, int rank, int size)
{
    double lower_bound = static_cast<double>(rank) / size;
    double upper_bound = static_cast<double>(rank + 1) / size;
    std::vector<double> batch_data_points;
    for (double data_pt : dataPoints) {
        if (data_pt >= lower_bound && data_pt < upper_bound) {
            batch_data_points.push_back(data_pt);
        }
    }
    return batch_data_points;
}
