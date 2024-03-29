# Makefile

CXX=g++
LIB_PATH = /home/l/lcl_uotphy1610/lcl_uotphy1610s2480/MyOpenBLAS/# Path to the OpenBLAS library
LIB_INC?=$(LIB_PATH)/include # Path to OpenBLAS include
LIB_LIB?=$(LIB_PATH)/lib # Path to OpenBLAS lib
CXXFLAGS= -I$(LIB_INC) -O2 -std=c++17
LDFLAGS= -L$(LIB_LIB)
LDLIBS= -lopenblas -lnetcdf_c++4 -lnetcdf # name of .so file of the library. Here it is located in lib directory and the name is libopenblas.so

OBJS= 1dlaplacesolver.o
OUTPUT_FILES = output.nc


all: 1dlaplacesolver


1dlaplacesolver.o: 1dlaplacesolver.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $< 

1dlaplacesolver: $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

run:
	./1dlaplacesolver

clean:
	rm -f $(OBJS) 1dlaplacesolver $(OUTPUT_FILES)
