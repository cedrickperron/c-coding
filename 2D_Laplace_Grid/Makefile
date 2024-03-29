# Makefile

CXX=g++
CXXFLAGS=-O3 -march=native
OBJS=laplacesolver.o gridinitialization.o outputgrid.o griditerator.o
OUTPUT_FILES = output.txt test.txt

all: laplacesolver

output.txt: laplacesolver
	./laplacesolver > output.txt

test.txt: laplacesolver
	./laplacesolver 50  > test.txt

laplacesolver: $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

laplacesolver.o: laplacesolver.cpp gridinitialization.h outputgrid.h griditerator.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $< 

gridinitialization.o: gridinitialization.cpp gridinitialization.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

outputgrid.o: outputgrid.cpp outputgrid.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

griditerator.o: griditerator.cpp griditerator.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

run: laplacesolver
	./laplacesolver

clean:
	$(RM) $(OBJS) $(TEST_TARGET) $(OUTPUT_FILES)

.PHONY: all clean # .PHONY means that you don't create a file of this name 
