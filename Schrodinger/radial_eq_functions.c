#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "radial_eq_functions.h"
#include "numerov_params.h"
#include "params.h"

#define alpha_EM (1.0/137.0)

// RadialEqFunctions_V(double r) is the only function one should change.
// This is in the unit of 1/fm
double RadialEqFunctions_V(double r)
{
 double f;
 double A, R_A, a, R0, V0;
 

 if(PARAM_DATA.nucA == 0) // TEST
  {
   f = -alpha_EM/r;
  }
 else{
 V0 = 50.0/hbarc; // MeV to 1/fm
 a = 0.7;
 R_A = PARAM_DATA.r0;
 f = -V0/(1.0 + exp((r-R_A)/a));
 }
 return f;
}// RadialEqFunctions_V

double RadialEqFunctions_Veff(double r)
{
 double f, ell, mass;
 ell = (double) PARAM_DATA.ell;
 
 mass = PARAM_DATA.mass;
 f = RadialEqFunctions_V(r) + ell*(ell+1)/(2*mass*r*r); 
 
 return f;
}//RadialEqFunctions_Veff

double RadialEqFunctions_F_Forward(double x, DynamicParams *D_Params)
{
 double x0, ka, r, f, g, Ea, Et, ell, eps;
 ell = (double) PARAM_DATA.ell;
 x0 = PARAM_DATA.x0;
 ka = PARAM_DATA.ka;
 Ea = PARAM_DATA.Ea;
 Et = D_Params->Et;
 
 eps = 1.0e-15;
 x += eps;
 r = x/ka;
 
 f = ell*(ell+1)/(x*x) + RadialEqFunctions_V(r)/Ea + Et;
 
 return f;
}//RadialEqFunctions_F_Forward

double RadialEqFunctions_F_Backward(double y, DynamicParams *D_Params)
{
 double ka, r, f, g, ell, Ea, Et, x, x0;
 ell = (double) PARAM_DATA.ell;
 x0 = PARAM_DATA.x0;
 ka = PARAM_DATA.ka;
 Ea = PARAM_DATA.Ea;
 Et = D_Params->Et;

 x = D_Params->xf - y;
 r = x/ka;
 
 f = ell*(ell+1)/(x*x) + RadialEqFunctions_V(r)/Ea + Et;
 
 return f;
}// RadialEqFunctions_F_Backward


