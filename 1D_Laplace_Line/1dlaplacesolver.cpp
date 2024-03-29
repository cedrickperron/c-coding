// main.cpp
#include <iostream>
#include <netcdf>
#include <tuple>
#include <rarray>
#include <lapacke.h>
#include <cmath>
#include <iomanip>

// Create epsilon matrix for all the steps (x = i * dx)
rarray<double, 1> create_epsilon(int N, double del_x) 
{ 
rarray<double, 1> epsilon(N+1);
for (int i = 0; i <= N; i++) 
{
    epsilon[i] = 1 + 10*std::pow(cos(2*M_PI*del_x*i), 2);
}
return epsilon;
}

// Create the matrix A and store its sub-diagonal, diagonal and super_diagonal components, which are inputs of the LAPLACK.
std::tuple<rarray<double, 2>, rarray<double, 1>, rarray<double, 1>, rarray<double, 1>> create_A(rarray<double, 1> epsilon, int N) 
{ 
rarray<double, 2> A(N-1, N-1);
rarray<double, 1> sub_diag(N-2);
rarray<double, 1> diag(N-1);
rarray<double, 1> sup_diag(N-2);

for (int i = 0; i <= N-3; i++) 
{ 
    // Make the sub_diagonal components of the matrix A
    sub_diag[i] =  epsilon[i+1]; 
    A[i+1][i] = sub_diag[i]; 

    // Make the diagonal components of the matrix A
    diag[i] = - ( epsilon[i+1] + epsilon[i]);
    A[i][i] = diag[i];

    // Make the super diagonal components of the matrix A
    sup_diag[i] = epsilon[i+1];
    A[i][i+1] = sup_diag[i];

}
// Add the last diagonal element of A
diag[N-2] = -(epsilon[N-1] + epsilon[N-2]);
A[N-2][N-2] = diag[N-2];
return std::make_tuple(A, sub_diag, diag, sup_diag);

}

// Create the column vector B (right-hand side)
rarray<double, 1> create_B(rarray<double, 1> epsilon, int N, rarray<double, 1> bdy_V) 
{ 
rarray <double, 1> B(N-1);
// Set the values of B to zeros
B.fill(0.0);
// Set the Bdy Conditions
B[0] = - epsilon[0]*bdy_V[0];
B[N-2] = -epsilon[N-2]*bdy_V[1];
return B;
}


// Complete the matrix V adding the boundary values at V_0 and V_N and the result of LAPACK (stored in B)
rarray<double, 1> update_V(rarray<double, 1> B, int N, rarray<double, 1> bdy_V)
{
rarray<double, 1> V(N+1);
// Write the Bdy Conditions
V[0] = bdy_V[0]; 
V[N] = bdy_V[1];

// Add the values of b to the values of updated_V
for (int i = 1; i <= N-1; i++) {V[i] = B[i-1];}

return V;
}

// Create an output netcdf file
void output_netcdf(rarray<double, 1> epsilon, rarray<double, 1> V) 
{
    // Set the dimensions (epsilon and V have the same dimensions)
    int nx = epsilon.extent(0);
    //int ny = epsilon.extent(1);

    // Create the netCDF file
    netCDF::NcFile dataFile("output.nc", netCDF::NcFile::replace);

    // Create the dimension
    netCDF::NcDim xDim = dataFile.addDim("x", nx);

    // Create the data variable for epsilon
    netCDF::NcVar epsilonVar = dataFile.addVar("epsilon", netCDF::ncDouble, {xDim});

    // Put the data in the file
    epsilonVar.putVar(epsilon.data());

    // Create the data variable for V
    netCDF::NcVar VVar = dataFile.addVar("V", netCDF::ncDouble, {xDim});

    // Put the data in the file
    VVar.putVar(V.data());

    // Add an attribute
    dataFile.putAtt("Creation date:", "March 12th, 2024");

    // Close the file
    dataFile.close();

    // Mention
    std::cout << "Data written to output.nc" << std::endl;
}



int main(int argc, char* argv[]) 
{
int N = 10000;

// Pass some rules to deal with the arguments of the main and introduce the -h functionality.
    try {
        if (argc > 1)
            N = std::stoi(argv[1]);
    } catch(...) {
        std::cout <<
            "Computes Nx1 grid of Laplace Solver \n\n"
            "Usage:\n"
            "  Laplace Solver [-h | --help] | [N]\n\n";
        if (std::string(argv[1]) != "-h" and std::string(argv[1]) !="--help") {
            std::cerr << "Error in arguments!\n";
            return 1;
        } else
            return 0;
    }


double del_x = (1.0-0.0)/(N); // Set dx
// Set Bdy values of V --> first element is V(x=0) and the second is V(x = 1). These are the bdy values
rarray<double,1> bdy_V(2); 
bdy_V[0] = 0.0;
bdy_V[1] = 1.0; 


// Create epsilon
rarray<double, 1> epsilon = create_epsilon(N, del_x);

// Create the matrix A (Define the different matrices component) 
rarray<double, 2> A;
rarray<double, 1> DL, D, DU;
std::tie(A, DL, D, DU) = create_A(epsilon, N);

// Create matrix B
rarray<double, 1> B;
B =  create_B(epsilon, N, bdy_V);
const int NRHS = 1;
const int ldb = NRHS;

// Setting missing variable to solve A* X = B
int info; 


info = LAPACKE_dgtsv(LAPACK_ROW_MAJOR, N-1, NRHS, DL.data(), D.data(), DU.data(), B.data(), ldb);

// Print an error if the function did not work
if (info != 0) {
        std::cerr << "DGTSV failed with error code: " << info << std::endl;
        return 1;
    }

// The values of V are stored in B. We want to add the Bdy conditions
rarray<double, 1> V = update_V(B, N, bdy_V); 

// Print output in a netCDF file
output_netcdf(epsilon, V);
return 0; 



}
