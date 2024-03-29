//outputcells_test.cpp
#include "outputcells.h"
#include <catch2/catch_all.hpp>

TEST_CASE("Output cells function produces expected output") {
    // Define a stringstream to capture the output
    SECTION("Case 1") {
    std::stringstream output1;

    // Define a Cells object representing a specific configuration
    Cells cells1 = {alive, dead, alive, dead, alive}; 

    // Call the output_cells function with the defined parameters
    output_cells(output1, 0, cells1);

    // Check if the output matches the expected result
    REQUIRE(output1.str() == "0\tI-I-I 0.6\n");
    }

    SECTION("Case 2") {
    std::stringstream output2;

    // Define a Cells object representing a specific configuration
    Cells cells2 = {dead, dead, dead, dead, dead}; 

    // Call the output_cells function with the defined parameters
    output_cells(output2, 0, cells2);

    // Check if the output matches the expected result
    REQUIRE(output2.str() == "0\t----- 0\n");
    }

    SECTION("Case 3") {
    std::stringstream output3;

    // Define a Cells object representing a specific configuration
    Cells cells3 = {alive, alive, alive, alive, alive}; 

    // Call the output_cells function with the defined parameters
    output_cells(output3, 0, cells3);

    // Check if the output matches the expected result
    REQUIRE(output3.str() == "0\tIIIII 1\n");
    }

    SECTION("Case 4") {
    // 
    std::stringstream output4; 

    // Define a Cells object representing a specific configuration
    Cells cells4 = {dead, alive, dead, alive, dead}; 

    // Call the output_cells function with the defined parameters
    output_cells(output4, 1, cells4); // The result is written in the file zoutput4

    // Check if the output matches the expected result
    REQUIRE(output4.str() == "1\t-I-I- 0.4\n");
    }
    SECTION("Case 5") {
    std::stringstream output5;

    // Define a Cells object representing a specific configuration
    Cells cells5 = {dead, alive, dead, alive, dead, alive, dead, alive, dead, alive};

    // Call the output_cells function with the defined parameters
    output_cells(output5, 2, cells5);

    // Check if the output matches the expected result
    REQUIRE(output5.str() == "2\t-I-I-I-I-I 0.5\n");
    }

}

