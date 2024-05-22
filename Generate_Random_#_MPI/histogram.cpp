#include "histogram.h"

// normalized and print a histogram
void print_normalized_histogram(const rarray<int, 1>& histogram, double dx, unsigned long long N)
{
    for (int i = 0; i < histogram.size(); i++) {
        double normalized_counts = static_cast<double>(histogram[i]) / N;
        std::cout << "[" << i*dx << " - " << (i+1)*dx << "]: " << normalized_counts << std::endl;
    }
    std::cout << "\n";
}

// Function to compute histogram from a sets of data_points
rarray<int, 1> compute_histogram(const std::vector<double>& data_points, double dx) 
{
    rarray<int, 1> histogram(static_cast<int>(1.0 / dx));
    histogram.fill(0);
    for (double data_pt : data_points) 
    {
        int which_bin = static_cast<int>(data_pt / dx);
        histogram[which_bin]++;
    }
    return histogram;
}

void add_to_global_hist(rarray<int, 1>& global_histogram, const rarray<int, 1>& histogram)
{
    for (int i = 0; i < global_histogram.size(); i++) 
    {
        global_histogram[i] += histogram[i];
    }
}
