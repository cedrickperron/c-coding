// open_ncfile.h
#ifndef OPEN_NCFILEH
#define OPEN_NCFILEH


#include "complex.h"
#include <netcdf>
#include <string>
#include <rarray>

using namespace netCDF;


rvector<complex> open_ncfile(std::string& filename);

#endif
