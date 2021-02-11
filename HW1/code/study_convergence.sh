#! /bin/bash

# For Trapezoidal Rule:

## Compile & run the serial code 5 times, & save the time values in a file
g++ trapezoidal_serial.cpp

{ echo "Trapezoidal Rule Serial Code:" ; } 1> trapezoidal_convergence.txt
for num_divs in 2 4 8 16 50 100 200 500 1000 2000 5000 10000
do
    { ./a.out $num_divs ; } 1>> trapezoidal_convergence.txt
done

# For Montecarlo Method:

## Compile & run the serial code 5 times, & save the time values in a file
g++ montecarlo_serial.cpp

{ echo "Montecarlo Method Serial Code:" ; } 1> montecarlo_convergence.txt
for num_sample_pts in 2 4 8 16 50 100 200 500 1000 2000 5000 10000 50000 100000 500000 1000000
do
    { ./a.out $num_sample_pts ; } 1>> montecarlo_convergence.txt
done