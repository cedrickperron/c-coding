// fillcells.h
//
// Contains an initialization routine for a two-dimensional array of cells 
//
// This code is part of assignment 10 of the 2024 Winter PHY1610 course.
//
// Ramses van Zon, 2024, University of Toronto
// 

#ifndef FILECELLSH
#define FILECELLSH

#include "celltype.h"

// Fill cells such that the fraction of alive cells is approximately
// target_alive_fraction. Approximately, because the fraction might not 
// be expressible as a fraction with a denominator of the size.
//
// @param  num_rows               the number of row 
// @param  num_columns            the number of columns
// @param  target_alive_fraction  the fraction of cells to be alive
//
// @returns a 1d array of cells that are alive or dead.
//
Cells initial_cells(int num_rows, int num_columns, double target_alive_fraction);

#endif
