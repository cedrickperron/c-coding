// gridinitialization.cpp
#include "gridinitialization.h"

// Create a NxN grid
rarray<double, 2> create_NbyN_array(int N, double fill_value)
{
     // Size of N x N (Including Boundary)
    rarray<double, 2> grid(N, N); // Create NxN matrix
    grid.fill(fill_value); // fill the grid with value fill_value
    
    // Fill the external Bdy to zeros
    for (int i = 0; i < N; i++) {
        grid[0][i] = 0.0; // Set the first row to zero
        grid[i][0] = 0.0; // Set the first col to zero
        grid[i][N-1] = 0.0; // Set the last col to zero
        grid[N-1][i] = 0.0; // Set the last row to zero
    }

    return grid;
}
