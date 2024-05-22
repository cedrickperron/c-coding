#!/bin/bash
#SBATCH -N 2
#SBATCH -n 32
#SBATCH -c 1
#SBATCH -t 1:00:00
#SBATCH -J histogram_job
#SBATCH -o /scratch/l/lcl_uotphy1610/lcl_uotphy1610s2480/HW9_Result/Scrap/output_%j.txt
#SBATCH -e /scratch/l/lcl_uotphy1610/lcl_uotphy1610s2480/HW9_Result/Scrap/error_%j.txt


source setup

# Run the program for 1 process and time it
{ time make run N=32 ; } 2> /scratch/l/lcl_uotphy1610/lcl_uotphy1610s2480/HW9_Result/time_32.txt > /scratch/l/lcl_uotphy1610/lcl_uotphy1610s2480/HW9_Result/output_32.txt
