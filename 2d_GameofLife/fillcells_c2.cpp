// fillcells_c2.h
#include "fillcells.h"
#include <catch2/catch_all.hpp>

// test, for numcells from 0 to 16, that filling a fraction 1.0 sets
// all states to alive
TEST_CASE("full fill")
{
    for (int numcells = 0; numcells < 16; numcells++) {
        Cells full = initial_cells(numcells, numcells, 1.0);
        for (bool state: full)
            REQUIRE(state == alive);
    }
}

// test, for numcells from 0 to 16, that filling a fraction 0.0 sets
// all states to dead
TEST_CASE("empty fill")
{
    for (int numcells = 0; numcells < 16; numcells++) {
        Cells empty = initial_cells(numcells, numcells, 0.0);
        for (bool state: empty)
            REQUIRE(state == dead);
    }
}

// test, for even numcells from 0 to 16, that filling a fraction 0.5
// sets every other states to alive
TEST_CASE("half fill")
{
    for (int numcells = 0; numcells < 16; numcells+=2) { // only consider exact fits
        Cells half = initial_cells(numcells, numcells/2, 0.5);
        for (int i=0; i<numcells; i++) {
            for (int j=0; j<numcells/2; j++) {
                // initial_cells documentation does not say which cells
                // are filled, but it turns out it starts with the second
                if ((i*half.extent(1)+j)%2==1) 
                    REQUIRE(half[i][j] == alive);
                else
                    REQUIRE(half[i][j] == dead);
            }
        }
    }
}


// test, for numcells from 0 to 16 divisible by 4, that filling a
// fraction 0.25 sets every fourth state to alive
TEST_CASE("quarter fill")
{
    for (int numcells = 0; numcells < 16; numcells+=4) { // only consider exact fits
        Cells quarter = initial_cells(numcells, numcells, 0.25);
        for (int i=0; i<quarter.size(); i++) {
            // initial_cells documentation does not say which cells
            // are filled, but it turns out it starts with the fourth
            if (i%4==3)
                REQUIRE(quarter.data()[i] == alive);
            else
                REQUIRE(quarter.data()[i] == dead);
        }
    }
}

// test, for even numcells from 0 to 16, that filling a fraction 0.15
// approximately sets 15% of states to alive
TEST_CASE("partial fill")
{
    for (int numcells = 0; numcells < 16; numcells++) {
        Cells partial = initial_cells(numcells, numcells, 0.15);
        int sum = 0;
        for (bool s: partial) 
            if (s) sum++;
        // initial_cells documentation does not say how it
        // approximates non-exact fits, but the following was
        // heuristally found to be satisfied.
        REQUIRE(sum == int(0.15*numcells*numcells));
    }
}
