# Usage for HW9

## Compilation

IN BOTH DIR:
`make`  will both generate an executable (laplace) from the source files. (Both in the main directory and in Step_4)



## Running

MAIN DIR:
`./mpi_random_main N=()`: run the main using N CPUs.

STEP_4 DIR:
`./new_main N=()`: run the main using N CPUs.



#### Batch Job
IN BOTH DIR:
`sbatch run_random_(N).sh`: run the executable using N CPUs. This is in both directory.

The results are printed in: `/scratch/l/lcl_uotphy1610/lcl_uotphy1610s2480/HW9_Result` which is a writable directory.
You can change the directory by adjusting the `run_random_(N).sh` files.

IN BOTH DIR:
`chmod +x run_all.sh` 
`./run_all.sh`: runs the executable for N = 1, 4, 16 and 32 CPUs.

The results are printed in: `/scratch/l/lcl_uotphy1610/lcl_uotphy1610s2480/HW9_Result` which is a writable directory.
You can change the directory by adjusting the `run_random_(N).sh` files.



### CLEANING
IN BOTH DIR:

To safely remove all executables and .o files, run `make clean` in terminal.
