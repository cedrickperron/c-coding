// updatecells.cpp
//
// See updatecells.h for documentation.
//
// This code is part of assignment 10 of the 2024 Winter PHY1610 course.
//
// Ramses van Zon, 2024, University of Toronto
//

#include "updatecells.h"

// Determine next state of a single cell based on the state of all the cells
bool next_cell_state(const Cells& cell_state, int row_index, int col_index) {
    int num_rows = cell_state.extent(0);
    int num_cols = cell_state.extent(1);
    int alive_neighbours = 0;
    #pragma omp parallel for reduction(+:alive_neighbours) default(none) shared(cell_state, row_index, col_index, num_rows, num_cols)
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i==0 and j==0) continue; // do not count yourself
            // note: the modulus operator (%) enforces periodic boundary
            // conditions
            if (cell_state[(row_index+i+num_rows)%num_rows]
                          [(col_index+j+num_cols)%num_cols] == alive)
                alive_neighbours++;
        }
    }
    if (cell_state[row_index][col_index] == alive and
        (alive_neighbours == 2 or alive_neighbours == 3))
        return alive;
    else if (cell_state[row_index][col_index] == dead and
             (alive_neighbours == 3))
        return alive;
    else
        return dead;
}

Cells update_all_cells(const Cells& oldcell) {
    int num_rows = oldcell.extent(0);
    int num_cols = oldcell.extent(1);
    Cells newcell(num_rows, num_cols);
    #pragma omp parallel for default(none) shared(newcell, oldcell, num_rows, num_cols)
    for (int i = 0; i < num_rows; i++) 
        #pragma omp parallel for shared(newcell, oldcell, num_rows, num_cols, i) default(none)
        for (int j = 0; j < num_cols; j++) 
            newcell[i][j] = next_cell_state(oldcell, i, j);
    return newcell;
}
