// outputcells.h
//
// Contains an output routine for cells 
//
// This code is part of assignment 10 of the 2024 Winter PHY1610 course.
//
// Ramses van Zon, 2024, University of Toronto
// 

#ifndef OUTPUTCELLSH
#define OUTPUTCELLSH

#include "celltype.h"
#include <ostream>

// Output time step, state of cells, and fraction of alive cells.
// The first line has the timestep, the state of row[0], & the fraction;
// Subsequent line contain the remaining rows.
//
// @param  out   an out-stream (for instance std::cout or an std::ofstream) to write to
// @param  step  the step value to include in the output
// @param  cell  the alive/dead cells
// 
void output_cells(std::ostream& out, int step, const Cells& cell);

// Output time step, linear coordinate of alive cells, and fraction of
// alive cells, on one line. This is more efficient that output_cells
// if the number of alive cells is low.  Note: The linear coordinate
// of a cell at row r and colymn c is defined as r*num_cols+c.
//
// @param  out   an out-stream (for instance std::cout or an std::ofstream) to write to
// @param  step  the step value to include in the output
// @param  cell  the alive/dead cells
// 
void output_alive_cells(std::ostream& out, int step, const Cells& cell);

#endif
