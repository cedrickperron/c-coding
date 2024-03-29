//updatecells_test.cpp
#include "fillcells.h" // We use the function initial_cells
#include "updatecells.h"
#include <catch2/catch_all.hpp>

TEST_CASE("updatecells_test") {
    SECTION("Case 1") {
    Cells cell = initial_cells(10, 1.0); // Creates a cell where all the components are alive
    // Define an Evolution loop of 5 steps
    int num_steps = 10;
    for (int t = 0; t < num_steps; t++) {
        // Update cells
        cell = update_all_cells(cell);
        // Iterate through each element of the cells and make sure that they are alive
        Cells::iterator iter = cell.begin(); // Create iter pointer
        bool all_alive = true; // Create a new bool parameter that will become false if the cell is not all alive
        for(iter; iter < cell.end(); iter++) {
        if(*iter == dead) { // If one cell element is dead, declare all_alive false and break the for loop
            all_alive = false; 
            break;}
        }
        REQUIRE(all_alive);
    }
    }
    SECTION("Case 2") {
    Cells cell = initial_cells(10, 0.0); // Creates a cell where all the components are dead
    // Define an Evolution loop of 5 steps
    int num_steps = 5;
    for (int t = 0; t < num_steps; t++) {
        // Update cells
        cell = update_all_cells(cell);
        
        // Iterate through each element of the cells and make sure that they are dead
        Cells::iterator iter = cell.begin(); // Create iter pointer
        bool all_dead = true; // Create a new bool parameter that will become false if the cell is not all dead
        for(iter; iter < cell.end(); iter++) {
        if(*iter == alive) { // If one cell element is alive, declare all_dead false and break the for loop
            all_dead = false; 
            break;}
        }
        REQUIRE(all_dead);
    }
    }
    SECTION("Case 3") {
    Cells cell = initial_cells(4, 0.7); // Create a configuration of cells -II- that evolves periodically. It goes from -II- -> I--I (repeat)
    
    REQUIRE((cell[0]==dead && cell[1]==alive && cell[2]==alive && cell[3]==dead)); // Check that the initial configurations is indeed of the form -II-
    // Define an Evolution loop of 5 steps
    int num_steps = 5;
    for (int t = 0; t < num_steps; t++) {
        // Update cells
        cell = update_all_cells(cell);

        // Check if the configurations of cell follow -II- (odd t) I--I (even t)
        if (t % 2 == 0) {
            REQUIRE((cell[0]==alive && cell[1]==dead && cell[2]==dead && cell[3]==alive));} //Check even t gives I--I
        if (t % 2 != 0) {
            REQUIRE((cell[0]==dead && cell[1]==alive && cell[2]==alive && cell[3]==dead));} //Check odd t gives -II-
        } 
    }
    
    }
