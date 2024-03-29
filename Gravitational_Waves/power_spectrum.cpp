//power_spectrum.cpp
#include "power_spectrum.h"


rvector<double> power_spectrum(rvector<complex> fhat)
{
    // Create a vector to store the power_spectrum values
    rvector<double> power_spectrum_val(fhat.size());
    for (int i = 0; i < fhat.size(); i++)
    {
        // Compute the power spectrum for every k as F_k = f_k . f_k^(\dag) = Re(f_k)^2 + Im(f_k)^2
        power_spectrum_val[i] = std::pow(fhat[i].real(), 2) + std::pow(fhat[i].imag(), 2);
    }
    return power_spectrum_val;

}
