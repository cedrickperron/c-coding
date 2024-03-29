// griditerator.h
#ifndef GRIDITERATORH
#define GRIDITERATORH

#include <rarray>
#include <cmath>

double gridpointij_maxchange(rarray<double, 2>& grid, int i, int j);

rarray<double,2> update_change_matrix(rarray<double, 2> change_matrix, rarray<double,2>& grid, int N, double threshold);


#endif

