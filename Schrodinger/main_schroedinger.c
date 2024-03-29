#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "numerov.h"
#include "numerov_params.h"
#include "radial_eq_functions.h"
#include "params.h"
#include "schroedinger.h"
#include "solve.h"
#include "init.h"
#include "vector_mtx.h"


void ReadInParams(char *input_file, DynamicParams *D_Params);

void ReadIn_N_Params(char *input_file_name, NumerovParams *N_Params_f, NumerovParams *N_Params_b);

void RecordParams(NumerovParams N_Params_f, NumerovParams N_Params_b);

void RecordResults(DynamicParams D_Params,NumerovParams N_Params_f, NumerovParams N_Params_b,double *yf, double *yb);

Params PARAM_DATA;


int main(int argc, char **argv)
{
 DynamicParams D_Params;
 NumerovParams N_Params_f;
 NumerovParams N_Params_b;

 double *yf, *yb;

 ReadInParams(argv[1], &D_Params); //Reads in the initial data. This is the first input file
 
 ReadIn_N_Params(argv[2], &N_Params_f, &N_Params_b);

 Init_CalcStaticScales(); //Get the Energy and Length Scales

 //Record The parameters
 RecordParams(N_Params_f, N_Params_b);
 

 // Allocate memory for the forward WF yf
 yf = vector_malloc(N_Params_f.nmax+1);
 // Allocate memory for the backward WF yb
 yb = vector_malloc(N_Params_b.nmax+1);
  
 Schroedinger_GetBoundState(&D_Params, &N_Params_f, &N_Params_b, yf, yb);
 RecordResults(D_Params, N_Params_f, N_Params_b, yf, yb);
 return 0;
}//main

void ReadInParams(char *input_file, DynamicParams *D_Params)
{
 FILE *input;
 double x, Et_max;
 int ix;
 char *mass_unit;
 double mass, nucA, nucZ;
 int ell;
 input = fopen(input_file, "r");
 
 fscanf(input, "%le", &mass);
 mass /= hbarc;
 PARAM_DATA.mass = mass;

 mass_unit = (char *)malloc(sizeof(char)*10);
 
 fscanf(input, "%s", mass_unit);
 PARAM_DATA.mass_unit = mass_unit;

 if(strcmp(mass_unit, "eV")==0) {PARAM_DATA.length_unit = "nm";}
 else if(strcmp(mass_unit, "MeV")==0) {PARAM_DATA.length_unit = "fm";}
 else {
  fprintf(stderr, "ReadInParams: %s is an unknown unit. \n", mass_unit);
  fprintf(stderr, "Known units are eV and MeV. \n");
  fprintf(stderr, "Exiting. \n");
  exit(0);
}
 fscanf(input, "%d", &ell);
 PARAM_DATA.ell = ell;

 fscanf(input, "%le", &nucA);
 PARAM_DATA.nucA = nucA;
 
 fscanf(input, "%le", &nucZ);
 PARAM_DATA.nucZ = nucZ;

 fscanf(input, "%le", &x);
 D_Params->Et_min=x;
 
 fscanf(input, "%le", &Et_max); //TEST
 D_Params->Et_max=Et_max;
 
 fclose(input);
 fprintf(stderr, "Done reading in. \n");
 return;
}// ReadInParams

void RecordParams(NumerovParams N_Params_f, NumerovParams N_Params_b)
{
 double x;
 int i;
 FILE *output;

 output = fopen("schroed_params.dat", "w");
 
 fprintf(output, "mass = %le \n", PARAM_DATA.mass*hbarc);
 fprintf(output, "Ea = %le \n", PARAM_DATA.Ea*hbarc);
 fprintf(output, "r0 = %le \n", PARAM_DATA.r0);
 fprintf(output, "ka = %le \n", PARAM_DATA.ka*hbarc);
 fprintf(output, "ell = %d \n", PARAM_DATA.ell);
 fprintf(output, "x0 = %le \n", PARAM_DATA.x0);
 fprintf(output, "nucA = %le \n", PARAM_DATA.nucA);
 fprintf(output, "nucZ = %le \n", PARAM_DATA.nucZ);
 fprintf(output, "nmaxf = %d \n", N_Params_f.nmax);

 fprintf(output, "x_i = %le \n", N_Params_f.x_i);
 fprintf(output, "x_f = %le \n", N_Params_f.x_f);
 fprintf(output, "y_0 = %le \n", N_Params_f.y_0);
 fprintf(output, "y_1 = %le \n", N_Params_f.y_1);
 fprintf(output, "h = %le \n", N_Params_f.h);
 
 fprintf(output, "nmaxb = %d \n", N_Params_b.nmax);
 fprintf(output, "x_f = %le \n", N_Params_b.x_f); 
 fprintf(output, "x_f = %le \n", N_Params_b.x_f);
 fprintf(output, "y_0 = %le \n", N_Params_b.y_0);
 fprintf(output, "y_1 = %le \n", N_Params_b.y_1);
 fprintf(output, "h = %le \n", N_Params_b.h);
 fclose(output);
 return;
}// RecordParams

void ReadIn_N_Params(char *input_file_name, NumerovParams *N_Params_f, NumerovParams *N_Params_b)
{
 FILE *input_file;
 double x;
 int ix;
 int nmax;

 input_file = fopen(input_file_name, "r");
 
 fscanf(input_file, "%d", &nmax);
 N_Params_f->nmax = nmax;
 
 fscanf(input_file, "%d", &nmax);
 N_Params_b->nmax = nmax; 

 fclose(input_file);

 return;
}//ReadIn_N_Params

void RecordResults(DynamicParams D_Params, NumerovParams N_Params_f, NumerovParams N_Params_b, double *yf, double *yb)
{
 double Et, Ea;
 FILE *output;
 int n;
 double x;

 output = fopen("schroedinger.dat", "w");
 Et = D_Params.Et;
 fprintf(output, "Et = %e\n", Et);
 Ea = PARAM_DATA.Ea;
 fprintf(output, "Eb = %e\n", Et*Ea*hbarc);
 
 fclose(output);
 
 output = fopen("yf.dat", "w");
 for(n=0; n<=N_Params_f.nmax; n++)
  {
   x = N_Params_f.x_i + n*N_Params_f.h; 
   x /= PARAM_DATA.ka;
   x *= hbarc;
   fprintf(output, "%e %e\n", x, yf[n]/yf[N_Params_f.nmax]);
  }
 fclose(output);
 
 output = fopen("yb.dat", "w");
 for(n=0; n<=N_Params_b.nmax; n++)
  {
    x = D_Params.xf - (N_Params_b.x_i + n*N_Params_b.h);
    x /= PARAM_DATA.ka;
    x *= hbarc;
    fprintf(output, "%e %e\n", x, yb[n]/yb[N_Params_b.nmax]); 
  }
 fclose(output);
}// RecordResults


