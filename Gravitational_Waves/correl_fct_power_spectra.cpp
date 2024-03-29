// correl_fct_power_spectra.cpp
#include "correl_fct_power_spectra.h"

double correl_fct_power_spectra(rvector<double> power_spectra1, rvector<double> power_spectra2)
{
    double correl_values, FG, FF, GG;
    FG = 0; FF = 0; GG = 0; // Initialize the value before the loop

    if (power_spectra1.size() != power_spectra2.size()) {
        throw std::runtime_error("Error: Power spectra sizes are not the same");
        return 0.0;
        }

    for (int i = 0; i < power_spectra1.size(); i++)
    {
        
        FG += power_spectra1[i]*power_spectra2[i]; // Inner product of power_spectra1 and power_spectra2
        FF += power_spectra1[i]*power_spectra1[i]; // Inner product of power_spectra1
        GG += power_spectra2[i]*power_spectra2[i]; // Inner product of power_spectra2
    }
    // Correlation function is def as: C_{F, G} = < F, G> / sqrt( <F, F> <G, G>)
    correl_values = FG/(std::sqrt(FF * GG));
    return correl_values;
}
