//power_spectrum.h
#ifndef POWER_SPECTRUMH
#define POWER_SPECTRUMH


#include "complex.h"
#include <rarray> 
#include <fftw3.h>

rvector<double> power_spectrum(rvector<complex> fhat);

#endif
