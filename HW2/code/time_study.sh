g++ -fopenmp mat_mul_upper_openmp.cpp

# { echo "OpenMP Parallelization:" ; } 1> openmp_timing.txt
# { echo "--------------------------------------"; } 1>> openmp_timing.txt
# for n in 100 500 1000 2000 5000
for n in 5000
do
    { echo "Matrix Dimension:" $n ; } | tee -a openmp_timing.txt
    { echo "----------------------"; } 1>> openmp_timing.txt
    for num_threads in 1 2 4 6 8
    do
        { echo "Number of Threads: " $num_threads ; } 1>> openmp_timing.txt

        { ./a.out $n $num_threads; } 1>> openmp_timing.txt


        { echo ; } 1>> openmp_timing.txt
    done
    { echo "----------------------"; } 1>> openmp_timing.txt
    { echo ; } 1>> openmp_timing.txt
done