//main2.cpp
#include <mpi.h>
#include "prng_example.h"
#include "filter_data_points.h"
#include "histogram.h"


int main(int argc, char** argv) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const unsigned long long N = 1000000000;
    const unsigned long long Z = 100000;
    const double dx = 0.015625;

    rarray<int, 1> global_histogram(static_cast<int>(1.0 / dx));
    global_histogram.fill(0);

    // Generate a batch of random numbers and compute the histogram locally
    for (unsigned long long i = 0; i < N / Z; i++) {
            std::vector<double> dataPoints(Z);
        for (unsigned long long j = 0; j < Z; j++) {
            dataPoints[j] = randomDouble(0);
        }

        std::vector<double> batch_data_points = filter_data_points(dataPoints, rank, size);


        //print_data_points(batch_data_points, rank);
        rarray<int, 1> batch_histogram = compute_histogram(batch_data_points, dx); 

        if (rank != 0) {
            MPI_Send(batch_histogram.data(), batch_histogram.size(), MPI_INT, 0, 0, MPI_COMM_WORLD);}
        else {add_to_global_hist(global_histogram, batch_histogram); }
    }
    
    if (rank == 0) 
    {
        for (unsigned long long i = 0; i < N / Z; i++) 
        {
            for (int p = 1; p < size; p++) 
            {
                rarray<int, 1> recv_histogram(static_cast<int>(1.0 / dx));
                MPI_Recv(recv_histogram.data(), recv_histogram.size(), MPI_INT, p, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                add_to_global_hist(global_histogram, recv_histogram);
            }

        }
    
        std::cout << "\n" << "Overall Global Histogram" << std::endl;
        print_normalized_histogram(global_histogram, dx, N);

    }


    MPI_Finalize();

    return 0;
}
