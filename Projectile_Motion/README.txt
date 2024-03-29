# ReadMe

Author: Cedrick Perron
Email address: cedrick.perron@mail.utoronto.ca

Compiler: gcc 

## Project overview
Find the optimal launch angle given the speed for a maximum horizontal displacement
Write a program to compute the optimal angle at which to kick a ball from 
the ground with a fixed speed such that it travels the farthest distance 
before hitting the ground.

Assume that there is no friction, so that the trajectory of the ball will 
be given by

𝑥(𝑡)=𝑣𝑡cos(𝜃)

𝑦(𝑡)=𝑣𝑡sin(𝜃)−𝑔𝑡2/2

Here, x and y are the horizontal and vertical position of the ball, t is 
time, g is the gravitational acceleration, v is the initial speed of the 
ball, and 𝜃 is the initial angle of the trajectory.

Your program should take the value of v as input from cin, find the angle 
for which the distance is maximal, and print out the value of the angle 
and the distance.

Although this problem can actually be solved exactly, your code should 
find the distance traversed by computing the trajectory of the ball at 
regular small time intervals.



##Description of files

-"angle.cpp": Main executable, ask the input of v by the user and find the optimal angle and horizontal distance. There we iterate over every angle, solve the maximum time before which y<0 and use this time to solve for x_max. We then take the largest x_max out of every angle iterated over.


## Usage
Usage is described in `Usage.md`.

