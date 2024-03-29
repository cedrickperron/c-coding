// outputgrid.cpp
#include "outputgrid.h"



// Print the grid
void output_grid(std::ostream& out, const rarray<double, 2>& grid, int N) { 
// Print the grid row by row. The Nth row is print first and the 0th row is print last
for (int i = N-1; i > -1; i--) {
    for (int j = 0; j < N; j++) {
        out << std::setprecision(2) << std::fixed;
        out << grid[i][j] << " ";
    }
    out << std::endl;
}
}
