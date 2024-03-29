// outputgrid.h
#ifndef OUTPUTGRIDH
#define OUTPUTGRIDH

#include <rarray>
#include <ostream> // New cout for file
#include <iomanip> //setprecision


void output_grid(std::ostream& out, const rarray<double, 2>& grid, int N);

#endif
