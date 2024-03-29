#ifndef PARAMS_H
#define PARAMS_H

# define hbarc (197.3) // MeV.fm = eV.nm

typedef struct params
{
 double mass;
 double Ea;
 double ka;
 double r0;
 double x0;
 int ell;

 char *mass_unit;
 char *length_unit;
 
 double nucA;
 double nucZ;
 
} Params;

typedef struct dynamic_params
{
 double Eb;
 double kb;
 double rc;
 double Et;
 double xc;
 double rf;
 double xf;
 double Et_min;
 double Et_max;
} DynamicParams;

extern Params PARAM_DATA; //

#endif
