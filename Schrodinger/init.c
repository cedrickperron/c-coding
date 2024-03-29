#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "params.h"
#include "init.h"
#include "radial_eq_functions.h"
#include "solve.h"
#include "extremum.h"
#include "derivatives.h"


double Init_Rmin_Function(double r);


void Init_CalcStaticScales(void)
{
 double r_min, r_init, E_min, Eb, mass, r_c, curvature;
 double R_A;
 FILE *output;
 mass = PARAM_DATA.mass; //TEST

 if(PARAM_DATA.nucA == 0.0)
  {
   r_init = 0.01;
   r_min = Extremum_GetExtremum(Init_Rmin_Function, r_init, &curvature); //TEST
   PARAM_DATA.r0 = r_min;
   E_min = Init_Rmin_Function(r_min);
   PARAM_DATA.Ea = fabs(E_min);
  }
 else
  {
   PARAM_DATA.r0 = 1.3*pow(PARAM_DATA.nucA, 1.0/3.0);
   PARAM_DATA.Ea = 50.0/hbarc;
  }

 PARAM_DATA.ka = sqrt(2*mass*PARAM_DATA.Ea); // TEDST
 PARAM_DATA.x0 = PARAM_DATA.ka*PARAM_DATA.r0; // TEST     
 
 return;
}//Init_CalcStaticScales


double Init_Rmin_Function(double r)
{
 double f, mass;
 
 mass = PARAM_DATA.mass;
 f = RadialEqFunctions_V(r)+1/(2*mass*r*r);
 return f;
}// Init_Rmin_function


