#!/bin/bash
#SBATCH -N 1
#SBATCH -n 4
#SBATCH -c 1
#SBATCH -t 1:00:00
#SBATCH -J histogram_job
#SBATCH -o /scratch/l/lcl_uotphy1610/lcl_uotphy1610s2480/HW9_Result/Scrap/output_%j.txt
#SBATCH -e /scratch/l/lcl_uotphy1610/lcl_uotphy1610s2480/HW9_Result/Scrap/eerror_%j.txt

source setup

# Run the program for 1 process and time it
{ time make run N=4 ; } 2> /scratch/l/lcl_uotphy1610/lcl_uotphy1610s2480/HW9_Result/time_4.txt > /scratch/l/lcl_uotphy1610/lcl_uotphy1610s2480/HW9_Result/output_4.txt
