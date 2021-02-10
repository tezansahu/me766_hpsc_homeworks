#! /bin/bash

# Set the format of time to return only the "real" time taken
TIMEFORMAT=%R

# For Trapezoidal Rule (using 10000000 divisions to clearly demonstrate time taken):
{ echo "Trapezoidal Rule (with 10000000 divisions):" ; } 1> logs_trapezoidal.txt

## Compile & run the serial code 5 times, & save the time values in a file
g++ trapezoidal_serial.cpp

{ echo "Serial Code:" ; } 1>> logs_trapezoidal.txt
for i in {1..5}
do
    { time ./a.out 10000000 | sed -n '2 p' ; } 2>> logs_trapezoidal.txt
done

{ echo ; } 1>> logs_trapezoidal.txt

## Compile & run the parallel code 5 times for different number of threads, & save the time values in a file
g++ -fopenmp trapezoidal_parallel.cpp

for num_threads in 2 4 6 8
do
    { echo "Number of Threads: " $num_threads ; } 1>> logs_trapezoidal.txt
    for i in {1..5}
    do
        { time ./a.out 10000000 $num_threads | sed -n '2 p' ; } 2>> logs_trapezoidal.txt
    done

    { echo ; } 1>> logs_trapezoidal.txt
done