// main file
#include <iostream>
#include "gridinitialization.h"
#include "outputgrid.h"
#include "griditerator.h"



int main(int argc, char* argv[]) 
{   
    // Default parameters
    int N = 500; // Might be a bit long (it's ~400 iterations for a 30x30 matrix)
    double threshold = 1e-6;
    // Pass some rules to deal with the arguments of the main and introduce the -h functionality.
    try {
        if (argc > 1)
            N = std::stoi(argv[1]);
        if (argc > 2)
            threshold = std::stoi(argv[2]);
    } catch(...) {
        std::cout <<
            "Computes NxN grid of Laplace Solver \n\n"
            "Usage:\n"
            "  Laplace Solver [-h | --help] | [N [threshold]]\n\n";
        if (std::string(argv[1]) != "-h" and std::string(argv[1]) !="--help") {
            std::cerr << "Error in arguments!\n";
            return 1;
        } else
            return 0;
    }

    rarray<double, 2> grid = create_NbyN_array(N, 1.0); // Create a grid with interior Bdy V=1
    rarray<double, 2> change_matrix = create_NbyN_array(N, 10.0+threshold); // Create the change_matrix with fill_value chosen so that the while loop passes at least once
    // Create a while loop that updates the components of the grid until the changes of all grid values is less than the threshold
    bool a = true; // while loop argument
    while (a){
    change_matrix = update_change_matrix(change_matrix, grid, N, threshold); // Update the grid and the change_matrix

    // Break the loop (set a = false) and re-do the loop (set a = true)  if there are elements of the change_matrix that are above the threshold. 
    a = false;
    for (int k = 1; k < N-1; k++) {
        for (int l = 1; l < N-1; l++) {
            if (change_matrix[k][l]-threshold > 0) {a = true; continue;} // if the change of a grid values (stored in change_matrix) is greater than the threshold, then the while loop continues
        }
    } 
    } 
// Print the final grid
output_grid(std::cout, grid, N);
return 1;

}
