// fillcells_test.cpp
#include "fillcells.h"
#include <catch2/catch_all.hpp>

TEST_CASE("fillcells_test") {
    
    SECTION("Case 1") {
    double target_alive_fraction = 0.78;
    Cells cells = initial_cells(5, target_alive_fraction); // Create a cell using the function of fillcells

    int size_cells = std::size(cells); // Get the size of the cell

    REQUIRE(size_cells == 5); // Make sure that the size of the cells is 20

    // Create a for loop that counts the number of dead and alive cells using a for loop
    int num_alive_cell = 0;
    int num_dead_cell = 0;
    Cells::iterator iter = cells.begin(); // Define a iterator elements
    for(iter; iter < cells.end(); iter++) {
        if (*iter == alive) {num_alive_cell +=1;} 
        if (*iter == dead) {num_dead_cell += 1;}
        } 
    // Calculate the expected number of alive and dead cells (round to the bottom for alive)
    int expected_num_alive_cell = std::floor(size_cells*target_alive_fraction);
    int expected_num_dead_cell = size_cells-expected_num_alive_cell;
    REQUIRE((num_alive_cell == expected_num_alive_cell && num_dead_cell == expected_num_dead_cell));
    }

    SECTION("Case 2") {
    double target_alive_fraction = 0.2;
    Cells cells = initial_cells(10, target_alive_fraction); // Create a cell using the function of fillcells

    int size_cells = std::size(cells); // Get the size of the cell

    REQUIRE(size_cells == 10); // Make sure that the size of the cells is 20

    // Create a for loop that counts the number of dead and alive cells using a for loop
    int num_alive_cell = 0;
    int num_dead_cell = 0;
    Cells::iterator iter = cells.begin(); // Define a iterator elements
    for(iter; iter < cells.end(); iter++) {
        if (*iter == alive) {num_alive_cell +=1;} 
        if (*iter == dead) {num_dead_cell += 1;}
        } 
    // Calculate the expected number of alive and dead cells (round to the bottom for alive)
    int expected_num_alive_cell = std::floor(size_cells*target_alive_fraction);
    int expected_num_dead_cell = size_cells-expected_num_alive_cell;
    REQUIRE((num_alive_cell == expected_num_alive_cell && num_dead_cell == expected_num_dead_cell));
    }
    SECTION("Case 3") {
    double target_alive_fraction = 0.5;
    Cells cells = initial_cells(20, target_alive_fraction); // Create a cell using the function of fillcells

    int size_cells = std::size(cells); // Get the size of the cell

    REQUIRE(size_cells == 20); // Make sure that the size of the cells is 20

    // Create a for loop that counts the number of dead and alive cells using a for loop
    int num_alive_cell = 0;
    int num_dead_cell = 0;
    Cells::iterator iter = cells.begin(); // Define a iterator elements
    for(iter; iter < cells.end(); iter++) {
        if (*iter == alive) {num_alive_cell +=1;} 
        if (*iter == dead) {num_dead_cell += 1;}
        } 
    // Calculate the expected number of alive and dead cells (round to the bottom for alive)
    int expected_num_alive_cell = std::floor(size_cells*target_alive_fraction);
    int expected_num_dead_cell = size_cells-expected_num_alive_cell;
    REQUIRE((num_alive_cell == expected_num_alive_cell && num_dead_cell == expected_num_dead_cell));
    }
    SECTION("Case 4") {
    double target_alive_fraction = 0.0;
    Cells cells = initial_cells(5, target_alive_fraction); // Create a cell using the function of fillcells

    int size_cells = std::size(cells); // Get the size of the cell

    REQUIRE(size_cells == 5); // Make sure that the size of the cells is 20

    // Create a for loop that counts the number of dead and alive cells using a for loop
    int num_alive_cell = 0;
    int num_dead_cell = 0;
    Cells::iterator iter = cells.begin(); // Define a iterator elements
    for(iter; iter < cells.end(); iter++) {
        if (*iter == alive) {num_alive_cell +=1;} 
        if (*iter == dead) {num_dead_cell += 1;}
        } 
    // Calculate the expected number of alive and dead cells (round to the bottom for alive)
    int expected_num_alive_cell = std::floor(size_cells*target_alive_fraction);
    int expected_num_dead_cell = size_cells-expected_num_alive_cell;
    REQUIRE((num_alive_cell == expected_num_alive_cell && num_dead_cell == expected_num_dead_cell));
    }
SECTION("Case 1") {
    double target_alive_fraction = 1.0;
    Cells cells = initial_cells(10, target_alive_fraction); // Create a cell using the function of fillcells

    int size_cells = std::size(cells); // Get the size of the cell

    REQUIRE(size_cells == 10); // Make sure that the size of the cells is 20

    // Create a for loop that counts the number of dead and alive cells using a for loop
    int num_alive_cell = 0;
    int num_dead_cell = 0;
    Cells::iterator iter = cells.begin(); // Define a iterator elements
    for(iter; iter < cells.end(); iter++) {
        if (*iter == alive) {num_alive_cell +=1;} 
        if (*iter == dead) {num_dead_cell += 1;}
        } 
    // Calculate the expected number of alive and dead cells (round to the bottom for alive)
    int expected_num_alive_cell = std::floor(size_cells*target_alive_fraction);
    int expected_num_dead_cell = size_cells-expected_num_alive_cell;
    REQUIRE((num_alive_cell == expected_num_alive_cell && num_dead_cell == expected_num_dead_cell));
    }

}
