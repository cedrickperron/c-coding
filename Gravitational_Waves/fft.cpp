// fft.cpp
#include "fft.h"

// Forward and Inverse Fourier tranform function taken from class notes
void fft_fast(rvector<complex>& f, rvector<complex>& fhat, bool inverse)
{
    const int n = f.size();
    const int sign = inverse*FFTW_BACKWARD+(1-inverse)*FFTW_FORWARD;
    fftw_plan p = fftw_plan_dft_1d(n,
                   reinterpret_cast<fftw_complex*>(f.data()),
                   reinterpret_cast<fftw_complex*>(fhat.data()),
                   sign,
                   FFTW_ESTIMATE);
    fftw_execute(p);
    fftw_destroy_plan(p);
}
 
