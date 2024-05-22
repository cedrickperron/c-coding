#include "celltype.h"
#include "fillcells.h"
#include "outputcells.h"
#include "updatecells.h"
#include <iostream>

int main(int argc, char* argv[]) {
    // Set default simulation parameters then accept command line arguments
    int R = 6;
    int C = 70;
    int T = 20;
    double F = 0.158;
    bool optimized_output = false;
    try {
        if (argc > 1) R = std::stoi(argv[1]);
        if (argc > 2) C = std::stoi(argv[2]);
        if (argc > 3) T = std::stoi(argv[3]);
        if (argc > 4) F = std::stod(argv[4]);
        if (argc > 5) optimized_output = std::stoi(argv[5]);
    } catch(...) {
        std::cout <<
            "\nComputes Conway's game of life\n\n"
            "Usage\n\n"
            "  gameof1d [-h|--help] | [R [C [T [F [OUTPUT]]]]]\n\n"
            ""
            "where\n\n"
            "  R  is the number of rows\n"
            "  C  is the number of columns\n"
            "  T  is the number of time steps to take\n"
            "  F  is the initial fraction of alive cells\n"
            " OUTPUT selects optimized output when sets to 1\n\n";
        if (std::string(argv[1]) != "-h" and std::string(argv[1]) !="--help") {
            std::cerr << "Error in arguments!\n";
            return 1;
        } else
            return 0;
    }
    // Simulation creation
    Cells cell = initial_cells(R, C, F);
    if (optimized_output)
        output_alive_cells(std::cout, 0, cell);
    else
        output_cells(std::cout, 0, cell);
    // Evolution loop
    for (int t = 0; t < T; t++) {
        // One step
        cell = update_all_cells(cell);
        // Output time step, state of cells, and fraction of alive cells
        if (optimized_output)
            output_alive_cells(std::cout, t + 1, cell);
        else
            output_cells(std::cout, t + 1, cell);
    }
} // end main
