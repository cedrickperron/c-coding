// fillcells_c2.h
#include "outputcells.h"
#include <catch2/catch_all.hpp>
#include <sstream>

TEST_CASE("test output")
{
    // testing output_cells function
    // needs a step to print out, start with an arbitrary value
    int knownstep = 125;
    // look at 5 different configurations that should be printed out
    for (std::string known : {"III","I-I","--I","II-","---"})
    {
        // convert to a Cells object
        Cells knowncells;
        knowncells.form({{known[0]=='I',known[1]=='I',known[2]=='I'},
                         {known[0]=='I',known[1]=='I',known[2]=='I'}});
        // determine alive fraction
        double sum = 0.0;
        for (bool x: knowncells) 
            sum += x;
        double knownfraction = sum/knowncells.size();
        // write known things out to a stringstrream, a ostream that
        // is a string (could be a file as well)
        std::stringstream s;
        output_cells(s, knownstep, knowncells);
        // now read it in again
        int readstep;
        std::string readstring1, readstring2;
        double readfraction;
        s >> readstep >> readstring1 >> readfraction >> readstring2;
        // and compare
        REQUIRE(readstep == knownstep);
        REQUIRE(readstring1 == known);
        REQUIRE(readstring2 == known);
        // the following is ready for the fact that the fractions are only written out with about 6 significant digits
        const double reltol = 1.0e-6;
        REQUIRE(fabs(readfraction - knownfraction) <= reltol*knownfraction);
        knownstep++; //next iteration uses the next knownstep
    }
}

TEST_CASE("test optimized output")
{
    // testing output_alive_cells function
    // needs a step to print out, start with an arbitrary value
    int knownstep = 125;
    // look at 5 different configurations that should be printed out
    for (std::string known : {"III","I-I","--I","II-","---"})
    {
        // convert to a Cells object
        Cells knowncells;
        knowncells.form({{known[0]=='I',known[1]=='I',known[2]=='I'},
                         {known[0]=='I',known[1]=='I',known[2]=='I'}});
        // determine alive fraction
        double sum = 0.0;
        for (bool x: knowncells) 
            sum += x;
        double knownfraction = sum/knowncells.size();
        // write known things out to a stringstrream, a ostream that
        // is a string (could be a file as well)
        std::stringstream s;
        output_alive_cells(s, knownstep, knowncells);
        // now read it in again
        int readstep;
        std::string readstring;
        double readfraction;
        s >> readstep >> readstring >> readfraction;
        // and compare
        REQUIRE(readstep == knownstep);
        std::string knownstring("/");
        for (int i=0;i<knowncells.size();i++)
            if (knowncells.data()[i]) knownstring += std::to_string(i)+"/";
        REQUIRE(readstring == knownstring);
        // the following is ready for the fact that the fractions are only written out with about 6 significant digits
        const double reltol = 1.0e-6;
        REQUIRE(fabs(readfraction - knownfraction) <= reltol*knownfraction);
        knownstep++; //next iteration uses the next knownstep
    }
}
