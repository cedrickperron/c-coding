#Makefile
CXX=g++
CXXFLAGS=-O3 -march=native
OBJS=rate_multiroots_solver.o rate_polynomialroot_solver.o
LIBS = -lgsl -lgslcblas -lm

all: rate_multiroots_solver rate_polynomialroot_solver

rate_multiroots_solver: rate_multiroots_solver.o
	$(CXX) $(LDFLAGS) -o $@ $^ $(LIBS)

rate_multiroots_solver.o: rate_multiroots_solver.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $< 

rate_polynomialroot_solver: rate_polynomialroot_solver.o
	$(CXX) $(LDFLAGS) -o $@ $^ $(LIBS)

rate_polynomialroot_solver.o: rate_polynomialroot_solver.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $< 

run: rate_multiroots_solver rate_polynomialroot_solver
	./rate_multiroots_solver
	./rate_polynomialroot_solver

clean:
	$(RM) $(OBJS) rate_multiroots_solver rate_polynomialroot_solver
