#!/bin/bash
#SBATCH --nodes=1
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=16
#SBATCH --time=4:00:00
#SBATCH --output=output_run_gameoflife.txt
#SBATCH --mail-type=FAIL

# Job parameters
NUM_ROWS=1000
NUM_COLS=1000
NUM_ITERATIONS=1000
DENSITY=0.183
SEED=1
MAX_THREADS=16
OUTPUT_FILE="runtimes.txt"

# Load environment settings
source teachsetup

# Compile the code
make

# Set OMP_PROC_BIND to true to bind OpenMP threads to physical processing units
export OMP_PROC_BIND=true

# Create a CSV file for storing runtimes
echo "NUM_THREADS,RUNTIME" > $OUTPUT_FILE

# Run the code for different numbers of threads
for ((threads=1; threads<=$MAX_THREADS; threads++)); do
    export OMP_NUM_THREADS=$threads
    start_time=$(date +%s.%N)
    ./gameoflife $NUM_ROWS $NUM_COLS $NUM_ITERATIONS $DENSITY $SEED > /dev/null
    end_time=$(date +%s.%N)
    runtime=$(echo "$end_time - $start_time" | bc)
    echo "$threads,      $runtime" >> $OUTPUT_FILE
done

echo "All runs completed. Results saved in $OUTPUT_FILE"
