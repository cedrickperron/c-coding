#ifndef EXTREMUM_H
#define EXTREMUM_H
//typedef double (*FuncPT)(double);
//double Extremum_GetExtremum(FuncPT ORIG_FUNC, double x_init, double *curvature);
double Extremum_GetExtremum(double (*func)(double), double x_init, double *curvature);
//double Extremum_DF(double x);



#endif
