#ifndef SCHROEDINGER_H
#define SCHROEDINGER_H
#include "params.h"
#include "numerov_params.h"



void Schroedinger_GetBoundState(DynamicParams *D_Params, NumerovParams *N_Params_f, NumerovParams *N_Params_b, double *yf, double *yb);

//void ReadInParams(char *input_file);

//void RecordParams(NumerovParams N_Params_f, NumerovParams N_Params_b);

//void ReadIn_N_Params(char *input_file_name, NumerovParams *N_Params_f, NumerovParams *N_Params_b);

//void RecordResults(DynamicParams D_Params, NumerovParams N_Params_f, NumerovParams N_Params_b, double *yf, double *yb);



#endif
