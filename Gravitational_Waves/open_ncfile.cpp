// open_ncfile.cpp
#include "open_ncfile.h"



rvector<complex> open_ncfile(std::string& filename)
{
    NcFile ncfile(filename.c_str(), NcFile::read);
    
/* // Check if problem with the file
    if (!ncfile.is_valid_file()) {
        std::cerr << "Error opening prediction file." << std::endl;
        return rvector<complex>(); // Return  an empty vector
    }
  */ 
    rvector<complex> frvector(ncfile.getDim("nt").getSize());
    ncfile.getVar("f").getVar(frvector.data());

    return frvector;

}
