#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "derivatives.h"
#include "extremum.h"
#include "solve.h"

typedef double (*FuncPT)(double); // FuncPT is a pointer to a function 
  				  // that takes in a double and
				  // returns a double

FuncPT ORIG_FUNC; // A common variable. Only valid within this file
double Extremum_DF(double x); // Used only within this file


double Extremum_GetExtremum(FuncPT func, double x_init, double *curvature)
{
 double x, tol, ddf;
 int count;
 tol = 1.0e-10;
 ORIG_FUNC = func; // To communicate with Extremum_DF 
 count = 0;
 x = Solve_Newton(0.0, Extremum_DF, x_init, tol, &count); //Don't need to call the x! Solve_Newton will assign the ExtrenumDF to x_init and so on!
 *curvature = Derivative_SecondD(x,func);
 return x; 
}// Extremum_GetExtremum

double Extremum_DF(double x)
{
 double f;
 
 f = Derivative_FirstD(x, ORIG_FUNC);
 
 
 return f;
}//Extremum_DF

 
 





