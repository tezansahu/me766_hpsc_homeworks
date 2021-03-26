#include <iostream>
#include <chrono>
#include <math.h>
#include <stdio.h>
#include <omp.h>


using namespace std;

int N_DEF = 1000;
int DEFAULT_NUM_THREADS = 1;

int N;
int num_threads;
int i, j, k;

// Perform matrix multiplication
void multiply(float A[][10000], float B[][10000], float C[][10000]) {
    // int C[N][N];
    
    #pragma omp parallel for shared(A, B, C) private(j, k)
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            C[i][j] = 0;
            for (k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Convert a matrix into upper triangular matrix using Gaussian elimination (row-transformations)
void convert_to_upper(float mat[][10000]) {
    float coeff;
    
    #pragma omp parallel for shared(mat) private(j, k, coeff)
    for (i = 0; i < N-1; i++) {
        #pragma omp parallel for
        for (j = i+1; j < N; j++) {
            coeff = mat[j][i] / mat[i][i];

            for (k = 0; k < N; k++) {
                mat[j][k] -= mat[i][k] * coeff;
            }
        }
    }
}

// Display a matrix
void display(float mat[][10000]) {
    for (i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%.2f\t", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main(int argc, char *argv[]){
    ///////////////////////////////////////////////////////
    // Arguments to be passed (all optional):            //
    //                                                   //
    // 1st: Matrix Dimensions                            //
    // 2nd: Number of threads to be used                 /
    //                                                   // 
    ///////////////////////////////////////////////////////

    if (argc == 1){
        N = N_DEF;
        num_threads = DEFAULT_NUM_THREADS;
    }
    else if (argc == 2){
        N = atoi(argv[1]);
        num_threads = DEFAULT_NUM_THREADS;
    }
    else if (argc == 3){
        N = atoi(argv[1]);
        num_threads = atoi(argv[2]);
    }
    else{
        cout<<"Invalid arguments. Exitting."<<endl;
        exit(1);
    }

    omp_set_num_threads(num_threads);

    // Declared as static so that they do not deside in stack & cause segmentation fault
    static float A[10000][10000], B[10000][10000], C[10000][10000];
    
    // Initialize matrices A & B to random floating point values (between 0 & 1)
    srand(0);
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            A[i][j] = rand() / (RAND_MAX * 1.0);
            B[i][j] = rand() / (RAND_MAX * 1.0);
        }
    }

    chrono::duration<double> elapsed_seconds;

    auto start_mul = chrono::system_clock::now();
    multiply(A, B, C);
    auto end_mul = chrono::system_clock::now();
    elapsed_seconds = end_mul - start_mul;
    printf("Matrix Multiplication: \t\t %.3f s\n", elapsed_seconds.count());
    
    // display(A);
    // display(B);
    // display(C);
    
    auto start_upper = chrono::system_clock::now();
    convert_to_upper(C);
    auto end_upper = chrono::system_clock::now();
    elapsed_seconds = end_upper - start_upper;
    printf("Upper Triangular Matrix: \t %.3f s\n", elapsed_seconds.count());

    elapsed_seconds = end_upper - start_mul;
    printf("Overall Time Taken: \t\t %.3f s\n", elapsed_seconds.count());
    
    // display(C);

}