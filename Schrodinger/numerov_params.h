#ifndef NUMEROV_PARAMS_H
#define NUMEROV_PARAMS_H
#include "params.h"

typedef double (*Func_1D)(double, DynamicParams *);

typedef struct numerov_params
{
 double x_f;
 double x_i;
 double y_0;
 double y_1;
 int nmax;
 double h;
 
 Func_1D NumerovFunc_F;

} NumerovParams;

#endif

