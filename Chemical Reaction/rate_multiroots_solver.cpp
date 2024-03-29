//MultirootSolver
#include <iostream>
#include <gsl/gsl_multiroots.h>

// Defining initial and constants parameters
struct rate_params{
    double k1; // Rate of forward reaction
    double k2; // Rate of backward reaction
    double x0; // Initial concentration of X
    double y0; // Initial concentration of Y
    double z0; // Initial concentration of Z
    }; 


// Functions of the rate_equations. Follow the format of the powells function 
// in the Multidimensional Root-Finding of the GSL library
int rate_equations(const gsl_vector *x, void *params_ptr, gsl_vector *f)
{
struct rate_params *params = (struct rate_params *) params_ptr;
double k1 = params->k1;
double k2 = params->k2;
double x0 = params->x0;
double y0 = params->y0;
double z0 = params->z0;

double c1 = x0 - 2 * y0; // Reactant concentration equality
double c2 = x0 + z0; // Product concentration equality

double X = gsl_vector_get(x, 0); // Concentration of X
double Y = gsl_vector_get(x, 1); // Concentration of Y
double Z = gsl_vector_get(x, 2); // Concentration of Z


// Define the 3 equations to be solving the roots for. The roots mean the right side =0
  gsl_vector_set(f, 0, k1 * X * X * Y - k2 * Z * Z); // First equation (chemical equilibrium)
  gsl_vector_set(f, 1, X - 2 * Y - c1);             // Second equation (cons. conc. of substrates x and y)
  gsl_vector_set(f, 2, X + Z - c2);                 // Third equation (cons. of conc. of substrates x and z)

return GSL_SUCCESS;
}

// Follow the gsl_multiroot_fsolver_hybrids of the Rosenbrock systems of equations
// in the Multidimensional Root-Finding of the GSL library
int main(void) 
{
    const gsl_multiroot_fsolver_type *T;
    gsl_multiroot_fsolver *s;
    struct rate_params params = {1.0, 0.7, 0.5, 1, 0}; // Choosing our values for the params of the rate_equations

    int status;
    size_t iter = 0; // Set the initializer iter 
    const size_t n = 3; // Number of variables
    gsl_multiroot_function f = {&rate_equations, n, &params}; // A gsl_multiroot_function is passed with the values of the params set in the initializer
    
    gsl_vector *x = gsl_vector_alloc(n); // Allocate a GLS vector to represent the params X, Y, Z values in the root
     
    // Setting the initial values for X, Y, Z to be the same as x0, y0, z0 specified in params
    gsl_vector_set (x, 0, 0.5); // Initial value of X
    gsl_vector_set (x, 1, 1);  // Initial value of Y
    gsl_vector_set (x, 1, 0);  // Initial value of Z


    T = gsl_multiroot_fsolver_hybrids;
    s = gsl_multiroot_fsolver_alloc(T, n);
    gsl_multiroot_fsolver_set(s, &f, x);
  
  do
    {
      iter++;
      status = gsl_multiroot_fsolver_iterate (s); // Perform one iterations of the solver s and check if the estimate of the roots is improved

      if (status)   /* check if solver is stuck */
        break;

      status =
        gsl_multiroot_test_residual (s->f, 1e-6); // Solve to 1 part in 1e6
    }
  while (status == GSL_CONTINUE && iter < 10000); // Solve until the system has not converged (GSL_CONTINUE) until iter < 10000


  std::cout << "status = " << gsl_strerror(status) << "\n"; // Print out whether this has been successfully achieved or if there is an error
  std::cout << "The equilibrium value of X is: " << gsl_vector_get(s->x, 0) << "\n";
  std::cout << "The equilibrium value of Y is: " << gsl_vector_get(s->x, 1) << "\n";
  std::cout << "The equilibrium value of Z is: " << gsl_vector_get(s->x, 2) << "\n";

return 0;

}
