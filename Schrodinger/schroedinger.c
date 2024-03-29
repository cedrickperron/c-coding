#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "numerov.h"
#include "numerov_params.h"
#include "radial_eq_functions.h"
#include "params.h"
#include "schroedinger.h"
#include "solve.h"
#include "init.h"
#include "derivatives.h"
#include "vector_mtx.h"

NumerovParams *COM_N_PARAMS_F;
NumerovParams *COM_N_PARAMS_B;
DynamicParams *COM_D_PARAMS;
double *COM_Y_F; // Forward wavefunction
double *COM_Y_B; // Backward wavefunction

double Schroedinger_GetDf_nmax(double *y, NumerovParams *N_Params);
void Schroedinger_InitializeCommonVar(void);
double Schroedinger_GetError(void);
void Schroedinger_EvolveForward(void);
void Schroedinger_EvolveBackward(void);
void Schroedinger_CalcRunScales(double Et);
double Schroedinger_CalcRc(double Eb, double r_init);
double Schroedinger_GetBoundStateError(double Et);
void Schroedinger_PlotData(double Et_min, double Et_max);

void Schroedinger_GetBoundState(DynamicParams *D_Params, NumerovParams *N_Params_f, NumerovParams *N_Params_b, double *yf, double *yb)
{
 double Et_min, Et_max, tol, err;
 int count;
 double x, y;
 COM_N_PARAMS_F = N_Params_f;
 COM_N_PARAMS_B = N_Params_b;
 COM_D_PARAMS = D_Params;
 COM_Y_F = yf;
 COM_Y_B = yb;
 Et_min = D_Params->Et_min;
 Et_max = D_Params->Et_max;
 
 Schroedinger_PlotData(Et_min, Et_max);
 count = 0;
 tol = 1.0e-6;
 Solve_Bisect(0.0, Schroedinger_GetBoundStateError, Et_min, Et_max, tol, &count);
 fprintf(stderr, "count = %d\n", count);
 return;

}// Schroedinger_GetBoundState

void Schroedinger_PlotData(double Et_min, double Et_max)
{
 FILE *output;
 int n, nmax;
 double dEt, Et, err;
 
 output = fopen("plot_data.dat", "w");
 
 nmax = 1000;
 dEt = (Et_max - Et_min)/(nmax);
 for(n=0; n<=nmax; n++)
  {
   Et = Et_min + n*dEt;
   err = Schroedinger_GetBoundStateError(Et);
   
   fprintf(output, "%e %e\n", Et, err);
  }
 fclose(output);
 return;
}// Schroedinger_Plot_Data

double Schroedinger_GetBoundStateError(double Et)
{
 double err;
 Schroedinger_CalcRunScales(Et);
 Schroedinger_InitializeCommonVar();
 Schroedinger_EvolveForward();
 Schroedinger_EvolveBackward();
 
 err = Schroedinger_GetError();
 
 return err;
}// Schroedinger_GetBoundStateError

void Schroedinger_CalcRunScales(double Et)
{
 double r_init, r_min, r_c, Ea, Eb, mass, ka, kb, xf;
 Ea = PARAM_DATA.Ea;
 Eb = Et*Ea;
 
 mass = PARAM_DATA.mass;
 COM_D_PARAMS->kb = sqrt(2.0*Eb*mass);
 
 COM_D_PARAMS->Et = Et; //TEST
 COM_D_PARAMS->Eb = Eb; //TEST
 
 r_min = PARAM_DATA.r0;
 r_init = 1.1*r_min;
 
 r_c = Schroedinger_CalcRc(Eb, r_init);
 
 ka = PARAM_DATA.ka;
 COM_D_PARAMS->rc=r_c;
 COM_D_PARAMS->xc=r_c*ka;
 
 kb = COM_D_PARAMS->kb;
 
 COM_D_PARAMS->xf=20*(ka/kb);
 xf = COM_D_PARAMS->xf;
 COM_D_PARAMS->rf=(xf/ka); //TEST
 
 return;
}//Schroedinger_CalcRunScales

double Schroedinger_CalcRc(double Eb, double r_init)
{
 double f, E_min, r_c, tol;
 int count;
 tol = 1.0e-8;
 count = 0;
 r_c = Solve_Newton(-Eb, RadialEqFunctions_Veff, r_init, tol, &count);
 
 return r_c;
} // Get the turning point larger than Rmin

void Schroedinger_InitializeCommonVar(void)
{
 double kb, rf, h;
 COM_N_PARAMS_F->x_i = 0.0;
 COM_N_PARAMS_F->x_f = COM_D_PARAMS->xc;
 COM_N_PARAMS_F->y_0 = 0.0;
 COM_N_PARAMS_F->y_1 = 0.1;
 COM_N_PARAMS_F->h = (COM_N_PARAMS_F->x_f-COM_N_PARAMS_F->x_i)/(COM_N_PARAMS_F->nmax);
 
 COM_N_PARAMS_B->x_i=0.0;
 COM_N_PARAMS_B->x_f = COM_D_PARAMS->xf-COM_D_PARAMS->xc;
 COM_N_PARAMS_B->h = (COM_N_PARAMS_B->x_f-COM_N_PARAMS_B->x_i)/(double)(COM_N_PARAMS_B->nmax);

 
 kb = COM_D_PARAMS->kb;
 rf = COM_D_PARAMS->rf;
 h  = COM_N_PARAMS_B->h;
 
 COM_N_PARAMS_B->y_0= exp(-kb*rf);
 COM_N_PARAMS_B->y_1= exp(-kb*(rf-h));
 
 return;
}//Schroeding_Initialize

void Schroedinger_EvolveForward(void)
{
 double f, df;
 int nmax;
 double *yf;
 NumerovParams *N_Params_f;
 DynamicParams *D_Params_f;

 yf = COM_Y_F;
 N_Params_f = COM_N_PARAMS_F;
 D_Params_f = COM_D_PARAMS;
 
 nmax = N_Params_f->nmax;
 
 N_Params_f->NumerovFunc_F=RadialEqFunctions_F_Forward;
 
 Numerov_Advance(yf, N_Params_f, D_Params_f);

 return;
}//Schroedinger_EvolveForward

void Schroedinger_EvolveBackward(void)
{
 double f, df;
 int nmax;
 double *yb;
 NumerovParams *N_Params_b;
 DynamicParams *D_Params_b;
 yb = COM_Y_B;
 N_Params_b = COM_N_PARAMS_B;
 D_Params_b = COM_D_PARAMS;
 nmax = N_Params_b->nmax;
 
 N_Params_b->NumerovFunc_F = RadialEqFunctions_F_Backward;
 
 Numerov_Advance(yb, N_Params_b, D_Params_b);
 
 return;

}//Schroedinger_EvolveBackward

double Schroedinger_GetDf_nmax(double *y, NumerovParams *N_Params)
{
 double df, h;
 int nmax;
 
 nmax = N_Params->nmax;
 h = N_Params->h;
 
 df = (3*y[nmax] - 4*y[nmax-1] + y[nmax-2])/(double)(2*h);
 
 return df;

}//Schroedinger_GetDf_nmax

double Schroedinger_GetError(void)
{
 double *yf, *yb;
 NumerovParams *N_Params_f, *N_Params_b;
 double df, df_f, df_b, db;
 N_Params_f = COM_N_PARAMS_F;
 N_Params_b = COM_N_PARAMS_B;
 yf = COM_Y_F;
 yb = COM_Y_B;
 //TEST OF DERIVATIVE
 df = Schroedinger_GetDf_nmax(yf, N_Params_f);
 df_f = df/(yf[N_Params_f->nmax]);
 db = Schroedinger_GetDf_nmax(yb, N_Params_b);
 df_b = -db/(yb[N_Params_b->nmax]);
 df = df_f - df_b;
 return df;
}//Schroedinger_GetError



