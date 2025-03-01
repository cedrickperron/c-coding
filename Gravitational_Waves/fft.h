// fft.h

#ifndef FFTH
#define FFTH

#include "complex.h"
#include <rarray> 
#include <fftw3.h>

void fft_fast(rvector<complex>& f, rvector<complex>& fhat, bool inverse);


#endif
