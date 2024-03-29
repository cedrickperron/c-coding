#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "numerov.h"
#include "numerov_params.h"
#include "vector_mtx.h"

void Numerov_Make_Fn(double *numerov_F, NumerovParams *N_Params, DynamicParams *D_Params);

void Numerov_Advance_A_Step(double *y, int n, double *numerov_F, NumerovParams *N_Params, DynamicParams *D_Params);


void Numerov_Advance(double *y, NumerovParams *N_Params, DynamicParams *D_Params)
 {
  double *numerov_F;
  int n;
  int nmax;
  
  nmax = N_Params->nmax;
  
  numerov_F = vector_malloc(nmax+1);
 
  Numerov_Make_Fn(numerov_F, N_Params, D_Params);
  
  y[0] = N_Params->y_0;
  y[1] = N_Params->y_1;
  
  for(n=2; n<=nmax; n++)
   {
    Numerov_Advance_A_Step(y, n, numerov_F, N_Params, D_Params);
   }
 
  return;
 }//Numerov_Advance

void Numerov_Make_Fn(double *numerov_F, NumerovParams *N_Params, DynamicParams *D_Params)
{
 int n;
 double x_n, x_i, h;
 
 for(n=0; n<=N_Params->nmax; n++)
  {
   x_i = N_Params->x_i;
   h = N_Params->h;
   x_n = x_i + h*n;
   numerov_F[n] = (N_Params->NumerovFunc_F)(x_n, D_Params);  //***Test_Function used in algo
 }
 return;
}//Numerov_make_Fn


void Numerov_Advance_A_Step(double *y, int n, double *numerov_F, NumerovParams *N_Params, DynamicParams *D_Params)
 {
  double h;
  double h2_over_12;

  h = N_Params->h; 
  h2_over_12 = (h*h)/12.0;
  

  y[n] = 0.0;  
  if(y[n-1] != 0.0)
   {
    y[n] += 2.0*(1 + 5.0*h2_over_12*numerov_F[n-1])*y[n-1];
   }
  if(y[n-2] != 0.0)
   {
    y[n] += -1.0*(1-h2_over_12*numerov_F[n-2])*y[n-2];
    y[n] /= (1 - h2_over_12*numerov_F[n]);
   } 
  return;
}//Numerov_Advance_A_Step


