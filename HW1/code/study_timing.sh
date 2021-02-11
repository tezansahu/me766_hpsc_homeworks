#! /bin/bash

# Set the format of time to return only the "real" time taken
TIMEFORMAT=%R

# For Trapezoidal Rule (using 10000000 divisions to clearly demonstrate time taken):

## Compile & run the parallel code 5 times for different number of threads, & save the time values in a file
g++ -fopenmp trapezoidal_parallel.cpp

{ echo "Trapezoidal Rule Parallel Code:" ; } 1> trapezoidal_timing.txt
for num_threads in 2 4 6 8
do
    { echo "Number of Threads: " $num_threads ; } 1>> trapezoidal_timing.txt
    for i in {1..5}
    do
        { time ./a.out 10000000 $num_threads | sed -n '2 p' ; } 2>> trapezoidal_timing.txt
    done

    { echo ; } 1>> trapezoidal_timing.txt
done

# For Montecarlo Method (using 10000000 sample points to clearly demonstrate time taken):

## Compile & run the parallel code 5 times for different number of threads, & save the time values in a file
g++ -fopenmp montecarlo_parallel.cpp

{ echo "Montecarlo Method Parallel Code:" ; } 1> montecarlo_timing.txt
for num_threads in 2 4 6 8
do
    { echo "Number of Threads: " $num_threads ; } 1>> montecarlo_timing.txt
    for i in {1..5}
    do
        { time ./a.out 10000000 $num_threads | sed -n '2 p' ; } 2>> montecarlo_timing.txt
    done

    { echo ; } 1>> montecarlo_timing.txt
done