# Makefile for gameof1d
#
# Part of assignment 3 for 2024 PHY1610
#
CXX=g++
CXXFLAGS=-O3 -march=native
OBJS=gameof1d.o fillcells.o updatecells.o outputcells.o
TEST_TARGET = outputcells_test outputcells_test.o fillcells_test fillcells_test.o updatecells_test updatecells_test.o

all: gameof1d originalgameof1d

integrated_test: originaltestoutput.txt testoutput.txt
	diff originaltestoutput.txt testoutput.txt

originaltestoutput.txt: originalgameof1d
	./originalgameof1d > originaltestoutput.txt

testoutput.txt: gameof1d
	./gameof1d > testoutput.txt

originalgameof1d: originalgameof1d.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

gameof1d: $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

gameof1d.o: gameof1d.cpp fillcells.h updatecells.h outputcells.h celltype.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $< 

fillcells.o: fillcells.cpp fillcells.h celltype.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

updatecells.o: updatecells.cpp updatecells.h celltype.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

outputcells.o: outputcells.cpp outputcells.h celltype.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

run: gameof1d
	./gameof1d

# TESTING

# Run the updatecells_test
run_updatecells_test: updatecells_test # The rule to run updatecells_test 
	./updatecells_test -s
# Create the executive files for updatecells_test
updatecells_test: updatecells_test.o updatecells.o fillcells.o
	$(CXX) -o $@ $^ -lCatch2Main -lCatch2
	
updatecells_test.o: updatecells_test.cpp fillcells.h updatecells.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<


# Run the fillcells_test
run_fillcells_test: fillcells_test #the rule to run fillcells_test
	./fillcells_test -s

# Create the executive files for fillcells_test
fillcells_test: fillcells_test.o fillcells.o
	$(CXX) -o $@ $^ -lCatch2Main -lCatch2

fillcells_test.o: fillcells_test.cpp fillcells.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

	
# Run the outputcells_test
run_outputcells_test: outputcells_test #the rule to run outputcells_test. 
	./outputcells_test -s

# Creating the executive files for outputcells_test.
outputcells_test: outputcells_test.o outputcells.o 
	$(CXX)  -o $@ $^ -lCatch2Main -lCatch2

outputcells_test.o: outputcells_test.cpp outputcells.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<
	

test: fillcells_test outputcells_test updatecells_test # This is the super rule to run all tests
	./outputcells_test -s
	./fillcells_test -s
	./updatecells_test -s

clean:
	$(RM) $(OBJS) $(TEST_TARGET)

.PHONY: run_outputcells_test run_fillcells_test run_updatecells_test # .PHONY means that you don't create a file of this name 
