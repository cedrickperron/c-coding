#include "updatecells.h"
#include <catch2/catch_all.hpp>

// A test to see that a state with all cells alive remains the same.
TEST_CASE("staying alive") {
    Cells cells_in;
    cells_in.form({{alive,alive,alive,alive},{alive,alive,alive,alive}});
    Cells cells_out = update_all_cells(cells_in);
    for (bool x: cells_in)
        REQUIRE(x==alive);
}

// A test to see that a state with all cells alive remains the same.
TEST_CASE("staying dead") {
    Cells cells_in;
    cells_in.form({{dead,dead,dead,dead},{dead,dead,dead,dead}});
    Cells cells_out = update_all_cells(cells_in);
    for (bool x: cells_in)
        REQUIRE(x==dead);
}

// A more interesting case.
TEST_CASE("more interesting") {
    Cells cells_in;
    cells_in.form({{dead, dead, alive, dead, dead, dead, alive, dead, alive, alive, alive},
                   {dead, dead, alive, dead, dead, dead, alive, dead, alive, alive, alive}});
    // use the rules in gameof1d.cpp which give: 
    Cells expected_cells_out;
    expected_cells_out.form({{alive,alive, alive,alive,dead, alive, alive,dead, dead,dead,dead},
                             {alive,alive, alive,alive,dead, alive, alive,dead, dead,dead,dead}});
    Cells cells_out = update_all_cells(cells_in);
    // check that it is correct
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 11; j++)
            REQUIRE(expected_cells_out[i][j] == cells_out[i][j]);
}
