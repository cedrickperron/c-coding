#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "solve.h"


double Solve_Get_Df(double (*func)(double), double x);
double Solve_Bisect
(double nu, double (*func)(double), double x_min, double x_max, double tol,
int *count) 
{
   double x_mid, f_max, f_min, f_mid, err;
   int count_max;
   count_max = 1000;
   *count += 1;
   x_mid = (x_min+x_max)/2.00;
   if(*count > count_max)
     {
      fprintf
      (stderr, "Solve_Bisect: Done %d iterations without convergence.\n",
       count_max);
      fprintf(stderr, "Exiting.\n");
      exit(0);
     }
   f_max = (*func)(x_max) - nu;
   f_min = (*func)(x_min)-nu;
   if(f_max*f_min >  0.0)
    {
     fprintf(stderr, "Solve_Bisect:  %f > 0.0, there is no solution within this range. \n", f_max*f_min);
     fprintf(stderr, "Exiting. \n");
     exit(0);
    }
   f_mid = (*func)(x_mid) - nu;
   if(nu != 0.0) {err = fabs(f_mid/nu);}
   else {err = fabs(f_mid);}
   if(err < tol) { return x_mid; }
   if(f_max*f_mid < 0.0)
    {
     return Solve_Bisect(nu, func, x_mid, x_max, tol, count);
    }
    else if(f_min*f_mid < 0.0)
     {
      return Solve_Bisect(nu, func, x_min, x_mid, tol, count);
     }
    else
     {
      if(f_mid==0.0) {return x_mid;}
      else if(f_max == 0.0) {return x_max;}
      else {return x_min;}
     }
}// BisectSolve

double Solve_Get_Df(double (*func)(double), double x_old)
 {
  double h, df;
   
    if(x_old != 0.0) { h = x_old*1.0E-5; }
    else {h = 1.0E-5; }
    df = (*func)(x_old+h) - (*func)(x_old-h);
    df /= 2.0*h;
  return df;
}//Solve_Get_Df


double Solve_Newton(double nu, double (*func)(double), double x_0, double tol, int *count)
{
 double x_old, x_new, err, df, h;
 int count_max;
 count_max = 1000;
 x_old = x_0;
 do {
     df = Solve_Get_Df(func, x_old);
     if(fabs(df) < tol)
     {
      fprintf(stderr, " Solve_Newton:  %f < %f, the derivative is too small. \n", fabs(df), tol);
      fprintf(stderr, "Exiting. \n");
      exit(0);
     }
    x_new = x_old +  (nu - (*func)(x_old))/df;
    err = fabs((x_new-x_old)/x_old);
    *&x_old = x_new; 
    *count += 1;
    if(*count == count_max)
     {
      fprintf(stderr, "Solve_Newton: Done %d iterations without convergence.\n",count_max);
      fprintf(stderr, "Exiting.\n");
      exit(0);
     }
    } while(err > tol);
 return x_new;
}// Solve_Newton
