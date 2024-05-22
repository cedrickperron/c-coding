// filecells.cpp
// 
// See filecells.h for documentation
//
// This code is part of assignment 10 of the 2024 Winter PHY1610 course.
//
// Ramses van Zon, 2024, University of Toronto
// 

#include "fillcells.h"

Cells initial_cells(int num_rows,
                    int num_columns,
                    double target_alive_fraction)
{
    Cells cell(num_rows, num_columns);
    // Fill cells such that the fraction of alive cells is approximately target_alive_fraction.
    double fill = 0.0;
    for (int i = 0; i < cell.size(); i++) {
        fill += target_alive_fraction;
        if (fill >= 1.0) {
            cell.data()[i] = alive;
            fill -= 1.0;
        } else
            cell.data()[i] = dead;
    }
    return cell;
}
