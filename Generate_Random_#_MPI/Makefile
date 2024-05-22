# Makefile for the MPI random

CXX = mpicxx
CXXFLAGS = -O2 -std=c++17 -march=native
LDFLAGS =
LIBS =

all: mpi_random_main

mpi_random_main: mpi_random_main.o filter_data_points.o histogram.o prng_example.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

histogram.o: histogram.cpp histogram.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

filter_data_points.o: filter_data_points.cpp filter_data_points.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

prng_example.o: prng_example.cpp prng_example.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

mpi_random_main.o: mpi_random_main.cpp histogram.h filter_data_points.h prng_example.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<


run: mpi_random_main
	mpirun -n $(N) ./mpi_random_main

clean:
	$(RM) histogram.o filter_data_points.o prng_example.o mpi_random_main.o

distclean: clean
	$(RM) mpi_random_main

