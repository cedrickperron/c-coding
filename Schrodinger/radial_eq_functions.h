#ifndef RADIAL_EQ_FUNCTIONS_H
#define RADIAL_EQ_FUNCTIONS_H
#include "params.h"

double RadialEqFunctions_V(double r);
double RadialEqFunctions_Veff(double r);
double RadialEqFunctions_F_Forward(double x, DynamicParams *D_Params);
double RadialEqFunctions_F_Backward(double x, DynamicParams *D_Params);

#endif


