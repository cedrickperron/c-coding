//Polynomial Roots solver
#include <iostream>
#include <gsl/gsl_poly.h>
#include <cmath>


// Following the example for the polynomal evaluation in the GSL library
int main (void)
{
    // Introducing the initial parameters:
    double k1 = 1.0;
    double k2 = 0.7;
    double x0 = 0.5;
    double y0 = 1.0;
    double z0 = 0.0;
    double c1 = x0 - 2*y0;
    double c2 = x0 + z0;


    // Define the properties of the polynomial
    int polynomial_degrees = 3; // Order of the polynomial
    double coefficients[4] = {-2*k2*c2*c2, 4*c2*k2, -(c1*k1+2*k2), k1}; // Coefficients of the polynomials
    double polynomial_roots[2*polynomial_degrees]; // Set where the roots of the polynomial will be allocated (2*i) will be the real val and (2i+1) will be the imaginary
    
    // Defining the workspace
    gsl_poly_complex_workspace * w = gsl_poly_complex_workspace_alloc (polynomial_degrees+1); // Allocate memory to solve the roots

    // Solve for the roots
    gsl_poly_complex_solve (coefficients, polynomial_degrees+1 , w, polynomial_roots);

    // Free the workforce memory
    gsl_poly_complex_workspace_free (w);

    int i; // Set initializer
    for (i = 0; i < polynomial_degrees; i++)
    {   
        /* Print only the value of the roots that is real. Since we cannot guarantee that
        the complex part will be exactly zero, we assume that zero means that it is a factor
        1e-10 smaller than the real part.
        */
        if (fabs(polynomial_roots[2*i+1]/polynomial_roots[2*i])< 1e-10)  
        {
        std::cout << " The equilibrium concentration of X is: " << polynomial_roots[2*i] << "\n";
        std::cout << "The equilibrium concentration of Y is: " << (-c1+polynomial_roots[2*i])/2 << "\n";
        std::cout << "The equilibrium concentration of Z is: " << (c2-polynomial_roots[2*i]) << "\n";
        }
    }

  return 0;
}
