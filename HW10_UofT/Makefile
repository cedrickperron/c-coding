# Makefile for gameoflife
#
# Starter code for assignment 10 for 2024 PHY1610
#
CXX=g++
CXXFLAGS=-O3 -march=native -Wall -fopenmp -pg
OBJS=gameoflife.o fillcells.o updatecells.o outputcells.o
LDLIBS= -fopenmp -lCatch2Main -lCatch2

all: gameoflife

# Integrated_test of the main file
integrated_test: test_ouput_1.txt test_ouput_2.txt test_ouput_3.txt original_output_1.txt original_output_2.txt original_output_3.txt
	diff original_output_1.txt test_ouput_1.txt
	diff original_output_2.txt test_ouput_2.txt
	diff original_output_3.txt test_ouput_3.txt

test_ouput_1.txt: gameoflife
	./gameoflife > test_ouput_1.txt

test_ouput_2.txt: gameoflife
	./gameoflife 10 10 10 0.30 > test_ouput_2.txt

test_ouput_3.txt: gameoflife
	./gameoflife 20 20 20 0.50 1 > test_ouput_3.txt


test: run_fillcells_c2 run_updatecells_c2 run_outputcells_c2

run_fillcells_c2: fillcells_c2 
	./fillcells_c2 -s

fillcells_c2: fillcells_c2.o fillcells.o
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

fillcells_c2.o: fillcells_c2.cpp fillcells.h celltype.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

run_updatecells_c2: updatecells_c2 
	./updatecells_c2 -s

updatecells_c2: updatecells_c2.o updatecells.o
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

updatecells_c2.o: updatecells_c2.cpp updatecells.h celltype.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

run_outputcells_c2: outputcells_c2
	./outputcells_c2 -s

outputcells_c2: outputcells_c2.o outputcells.o
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

outputcells_c2.o: outputcells_c2.cpp outputcells.h celltype.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

gameoflife: $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS) -pg

gameoflife.o: gameoflife.cpp fillcells.h updatecells.h outputcells.h celltype.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $< 

fillcells.o: fillcells.cpp fillcells.h celltype.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

updatecells.o: updatecells.cpp updatecells.h celltype.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

outputcells.o: outputcells.cpp outputcells.h celltype.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

run: gameoflife
	./gameoflife

clean:
	$(RM) $(OBJS) fillcells_c2.o  outputcells_c2.o updatecells_c2.o

distclean: clean
	$(RM) fillcells_c2 gameoflife outputcells_c2 updatecells_c2
