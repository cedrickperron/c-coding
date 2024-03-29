#include <iostream>
#include <string>
#include <cmath>
// Define constants
double g = 9.81;
double pi = M_PI;
// Define the functions
double max_time(double v, double theta); // Solve the final time when y = 0
double max_range(double v, double theta, double time);

double max_time(double v, double theta) {
    double angle = theta*pi/180;
    double del_t = v/2/g/10000;// Define the time_step
    double y[2] = {1.0,1.0}; // Define the y_values for iterations
    int N = 1;
    while (y[1] >  0.0) {
        y[1] = y[0];
        y[1] = v*del_t*N*sin(angle) - g*pow(del_t*N,2)/2;
        N+=1;
    }
    return (N-1)*del_t;
}

double max_range(double v, double theta, double time) {
    double angle = theta*pi/180;
    double x_max = v*cos(angle)*time;
    return x_max;
}


int main() {
    try { 
    double v;
    std::cout << "Initial speed of the ball: ";
    std::cin >> v;
    if (v <= 0) { throw std::invalid_argument("The speed must be greater than zero. \n"); }
    double theta, x_max=-1.0, optimal_angle = 0.0;
    for (theta = 0.0; theta <= 90.0; theta += 0.5) {
        double ftime  = max_time(v,theta);
        double x = max_range(v, theta, ftime); 
        //std::cout << "Time, Angle, x: " << time << " "  << theta << " " << x << "\n";
        if (x > x_max) {
        x_max = x;
        optimal_angle = theta;
        }
        } 
    std::cout << "The optimal angle is: " << optimal_angle << "\n";
    std::cout << "The maximum range is: " << x_max << "\n"; 
        } catch(const std::invalid_argument & e) { std::cerr << e.what() << std::endl; return 1;}
//std::cout << "The optimal angle is: " << optimal_angle << "\n";
//std::cout << "The maximum range is: " << x_max << "\n";
//std::cout << "Confirmation: " << pow(v,2)*sin(2*optimal_angle*pi/180)/g;
return 0;
} 
