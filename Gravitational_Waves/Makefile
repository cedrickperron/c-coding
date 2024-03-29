# Makefile for grav_waves_main
#
# Part of assignment 7 for 2024 PHY1610
#
CXX=g++
CXXFLAGS=-O3 -march=native
OBJS=correl_fct_power_spectra.o fft.o open_ncfile.o power_spectrum.o grav_waves_main.o
LDLIBS= -lfftw3 -lnetcdf_c++4 -lnetcdf


.PHONY: all run clean

all: grav_waves_main


grav_waves_main: $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

grav_waves_main.o: grav_waves_main.cpp correl_fct_power_spectra.h fft.h open_ncfile.h power_spectrum.h complex.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $< 

open_ncfile.o: open_ncfile.cpp complex.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

correl_fct_power_spectra.o: correl_fct_power_spectra.cpp complex.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

power_spectrum.o: power_spectrum.cpp complex.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

fft.o: fft.cpp complex.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<


run: grav_waves_main
	./grav_waves_main

clean:
	$(RM) $(OBJS)
