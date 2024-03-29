#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "derivatives.h"


double Derivative_FirstD(double x, double (*func)(double))
{
 double df, h;
 h = 1.0e-5;

 if(x != 0)
  {
  h = h*x;
  //printf("h = %e\n",h);
  }

 df = ((*func)(x+h)-(*func)(x-h))/(2*h);

 return df;
}//Derivative_FirstD

double Derivative_SecondD(double x, double (*func)(double))
{
 double ddf, h;
 h = 1.0e-5;

 if(x != 0) 
  {
  h = h*x;
  //printf("h = %e\n",h);
  }
 ddf = ((*func)(x+h)+(*func)(x-h)-2*(*func)(x))/(h*h);

 return ddf;
} //Derivative_SecondD
