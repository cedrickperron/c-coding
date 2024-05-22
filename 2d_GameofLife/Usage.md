# Usage for HW10

## Compilation

`make`  will both generate an executable (gameoflife) from the source files.


## Running

`make run`  will print the output of ./gameoflife



## TESTING

`make test_integrated`  will create the `test_ouput_(N).txt` (N = 1, 2, 3) files and compare them with `original_output_(N).txt` (unparallelized gameoflife) (N = 1, 2, 3). It is expected that the N = 3 files are different after parallelization, because the order of the printing might change.

`make test_ouput_(N).txt`  (N = 1, 2, 3) will create a file `make test_ouput_(N).txt` containing the output of ./gameoflife parallelized.

`make test`  will test instances of fillcells.cpp, updatecells.cpp and outputcells.cpp and make sure that there is no deviation with expected values.

`make run_fillcells_c2`  will test some instances of fillcells.cpp only and make sure that there is no deviation with expected values.

`make run_outputcells_c2`  will test some instances of outputcells.cpp only and make sure that there is no deviation with expected values. We expect that there are some issues with this, because the order of the printing for OUPUT = 1 changes after parallelization.
>>>
outputcells_c2.cpp:74: FAILED:
  REQUIRE( readstring == knownstring )
with expansion:
  "/5/3/1/0/4/2/" == "/0/1/2/3/4/5/"
<<<

`make run_updatecells_c2`  will test some instances of updatecells.cpp only and make sure that there is no deviation with expected values.


## GPROF
`gmon.out`: Profiling file created after running `./gameoflife`

`analysis1.txt`: Analysis of the gprof for the `./gameoflife 100 100 100`  where `gameoflife` was NOT parallelized.
>>> (gprof ./gameoflife 100 100 100 gmon.out > analysis1.txt)

`analysis2.txt`: Analysis of the gprof for the `./gameoflife 100 100 100`  where `gameoflife` was parallelized.
>>> (gprof ./gameoflife 100 100 100 gmon.out > analysis2.txt)

<<< RESULTS: We can see that next_cell_state, update_all_cells, output_cells run faster after parallelization >>>

### CLEANING

To safely remove all executables and .o files, run `make clean` in terinal.
