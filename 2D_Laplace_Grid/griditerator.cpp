// griditerator.cpp
#include "griditerator.h"

// Update dynamically the gridpoint (i, j) and calculate the max_change
double gridpointij_maxchange(rarray<double, 2>& grid, int i, int j) {
    double old_value = grid[i][j]; // Storing the old value
    grid[i][j] = (grid[i][j-1]+grid[i][j+1]+grid[i-1][j]+grid[i+1][j])/4.0; // Update the new value of the grid (since grid is called as a pointer, the value of the grid will be changed dynamically)
    double max_change = std::abs(grid[i][j] - old_value);    // Computing the max change
    return max_change;
}

// Update the values of all gridpoints (except Bdy) except the boundary points and update the value of the change_matrix for convergence analysis
rarray<double,2> update_change_matrix(rarray<double, 2> change_matrix, rarray<double,2>& grid, int N, double threshold) {
    
    double dx = 2.0/(N-1); // 2.0, because we reparametrize the matrix so that the bottom-left point is [0, 0]
    int N1 = std::round(0.9/dx); // Solve the rounded row/col integer corresponding to the interior boundary (V = 1)
    int N2 = std::round(1.1/dx); // Solve the rounded row/col integer corresponding to the interior boundar (V = 1)

    for (int i=1; i < N-1; i++) {
        for (int j=1; j<N-1; j++) {
            if ((i >= N1 && i <= N2) && (j >= N1 && j <= N2)) {change_matrix[i][j] = 0.0; continue;} // Do not change the element inside and on the interior boundary
            change_matrix[i][j] = gridpointij_maxchange(grid, i, j);
        }

    }
    return change_matrix;
}
