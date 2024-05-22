// outputcells.cpp
//
// see outputcells.h for documentation
//
// This code is part of assignment 10 of the 2024 Winter PHY1610 course.
//
// Ramses van Zon, 2024, University of Toronto
// 

#include "outputcells.h"

void output_cells(std::ostream& out, int step, const Cells& cell)
{
    const int num_rows = cell.extent(0);
    const int num_cols = cell.extent(1);
    const char on_char = 'I', off_char = '-';
    double alive_fraction = 0.0;
    for (auto& onecell: cell)
        if (onecell == alive)
            alive_fraction++;
    alive_fraction /= cell.size();
    out << step << "\t";
    for (int j = 0; j < num_cols; j++)
        if (cell[0][j] == alive)
            out << on_char;
        else
            out << off_char;
    out << " " << alive_fraction << "\n";
    for (int i = 1; i < num_rows; i++) {
        out << "\t";
        for (int j = 0; j < num_cols; j++)
            if (cell[i][j] == alive)
                out << on_char;
            else
                out << off_char;
        out << "\n";
    }
}

void output_alive_cells(std::ostream& out, int step, const Cells& cell)
{
    const int num_rows = cell.extent(0);
    const int num_cols = cell.extent(1);
    double alive_fraction = 0.0;
    #pragma omp parallel for default(none) reduction(+:alive_fraction) shared(cell)
    for (auto& onecell: cell) {
        if (onecell == alive)
            alive_fraction++;
    }
    rvector<int> alive_list(alive_fraction);
    int n = 0;
    #pragma omp parallel for default(none)  shared(num_rows, num_cols, alive_list, n, cell) collapse(2)
    for (int i = 0; i < num_rows; i++) 
    {
        for (int j = 0; j < num_cols; j++) 
        {
	        if (cell[i][j] == alive) 
	        {
	        #pragma omp critical
	        {
		    alive_list[n++] = i*num_cols + j;
            }
		    }
        }
	}
    alive_fraction /= cell.size();
    out << step << "\t/";
    #pragma omp parallel for default(none) shared(alive_list, out)
    for (const auto& x: alive_list)
        #pragma omp critical 
        {
        out << x << '/';
        }
    #pragma omp critical
    {
    out << "\t" << alive_fraction << "\n";
    }
}
