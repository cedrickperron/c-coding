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
    // Create a global histogram
    rarray<int, 1> global_histogram(static_cast<int>(1.0 / dx)); global_histogram.fill(0);
    if (rank == 0) 
    {
        // Iterate over batches
        for (unsigned long long i = 0; i < N / Z; i++) 
        {
            
            // Create a rarray containing the random number of the batches
            rarray<double, 1> dataPoints(Z);
            for (unsigned long long j = 0; j < Z; j++) {
                dataPoints[j] = randomDouble();
            }
            // Filter the list of random number into intervals [rank, (rank+1)/size) to be sent to CPU (rank)
            for (int p = 0; p < size; p++) {
                std::vector<double> batch_data_points = filter_data_points(dataPoints, p, size);
                // Send those corresponding those interval of p = rank != 0 to be processed by CPU (rank = p)
                if (p != 0) {
                    // Send size of batch data to CPU p
                    int batch_size = batch_data_points.size();
                    MPI_Send(&batch_size, 1, MPI_INT, p, 0, MPI_COMM_WORLD);
                    MPI_Send(batch_data_points.data(), batch_data_points.size(), MPI_DOUBLE, p, 0, MPI_COMM_WORLD);
                    
                } else 
                {
                    // For the data_points in the interval [0, 1/size) (that is of rank = 0), adds it to the global_histogram
                    rarray<int, 1> batch_histogram;
                    batch_histogram = compute_histogram(batch_data_points, dx);
                    add_to_global_hist(global_histogram, batch_histogram);
                }
            }
        }
    } else 
    {
        // Receive and process batches
        for (unsigned long long i = 0; i < N / Z; i++) 
        {
            // Receive the batch data
            int received_batch_size;
            MPI_Recv(&received_batch_size, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            std::vector<double> received_batch_data(received_batch_size);
            MPI_Recv(received_batch_data.data(), received_batch_data.size(), MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            // Compute the histogram from the received_batch_data
            rarray<int, 1> batch_histogram = compute_histogram(received_batch_data, dx);
            // Send processed data back to rank 0
            MPI_Send(batch_histogram.data(), batch_histogram.size(), MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
    }

/*
Add the histogram computed by CPUp (in the else loop) to the global histogram of CPU0. We need to iterate over each batch, otherwise
it just adds up one batch.
*/
    if (rank == 0) 
    {
        // Receive and aggregate histograms from other ranks
        for (unsigned long long i = 0; i < N / Z; i++) 
        {
            for (int p = 1; p < size; p++) 
            {
                // Receive histogram from rank p
                rarray<int, 1> recv_histogram(static_cast<int>(1.0 / dx)); // Placeholder histogram
                MPI_Recv(recv_histogram.data(), recv_histogram.size(), MPI_INT, p, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

                // Add received histogram to the global histogram
                add_to_global_hist(global_histogram, recv_histogram);
            }
        }
            // Print the final normalized histogram
            print_normalized_histogram(global_histogram, dx, N);
    } 


    MPI_Finalize();

    return 0;
}
