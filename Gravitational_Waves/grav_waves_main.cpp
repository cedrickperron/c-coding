#include "complex.h"
#include "fft.h"
#include "power_spectrum.h"
#include "correl_fct_power_spectra.h"
#include "open_ncfile.h"
#include <algorithm>
#include <iostream>

int main() {

    // Name of the prediction file
    std::string pred_file = "./data/GWprediction.nc";
    rvector<complex> fpred = open_ncfile(pred_file); // open pred file and stores signals f values
    
    rvector<complex> fpred_hat(fpred.size()); // Space for the Fourier transform of fpred
    fft_fast(fpred, fpred_hat, false); // fourier transform the signals of the prediction.
    rvector<double> power_spectrum_pred = power_spectrum(fpred_hat); // compute the power_spectrum of prediction signal

    // Open the ncfile of the different signals and stores it 
    const int num_of_signals = 32;

    // rarray that we will store the power_spectrum of the signal of the detection files
    rarray<rvector<double>, 1> power_spectrum_detection(num_of_signals);
    
    // Define some recurring parameters in the loop that will be updated every iteration
    std::string detection_filename; // store the filename
    rvector<complex> fdetection; // store the f values of the signal

    for (int i = 1; i <= num_of_signals; i++) 
    {
        // GET THE NAME OF THE FILE:::
        // The first 9 files are written as detection01.nc, detection02.nc (need to add a 0 after detection)
        if (i <= 9) {detection_filename = "./data/detection0" + std::to_string(i) + ".nc";}
        // The files from 10 to 32 are written without the zeros.
        else {detection_filename = "./data/detection" + std::to_string(i) + ".nc"; }

        // OPEN THE FILE AND STORE f:::
        fdetection = open_ncfile(detection_filename);
        
        // TAKE THE FFT OF THE DETECTION SIGNAL
        rvector<complex> fdetection_hat(fdetection.size()); // store the Fourier transform of the f values of the signal
        fft_fast(fdetection, fdetection_hat, false);
        
        // CALCULATE THE POWER SPECTRUM OF DETECTION SIGNAL AND STORE IT
        power_spectrum_detection[i-1] =   power_spectrum(fdetection_hat);
    }

    // Compute the correlation function between the power_spectrum of predicted signal and the one from detections
    rvector<double> correl_values(num_of_signals);

    for (int i = 0; i < num_of_signals; i++)
    {
        correl_values[i] = correl_fct_power_spectra(power_spectrum_pred, power_spectrum_detection[i]);
    }

    
    // SORT THE CORRELATION FUNCTION VALUES AND KEEP TRACK OF THE INDEX
    std::vector<int> indices(num_of_signals);
    std::iota(indices.begin(), indices.end(), 0);

    std::sort(indices.begin(), indices.end(), [&correl_values](int i, int j) {
    return correl_values[i] > correl_values[j];
});

    for (int i = 0; i < 5; i++)
    {
        int idx = indices[i];
        std::cout << "The " << i+1 << " largest correlation values are detection file #" << idx+1 << " And the value is " << correl_values[idx] << std::endl;
    }

    return 0;
}
