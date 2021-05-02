#include <iostream>
#include <math.h>
#include <stdio.h>
#include <time.h>

using namespace std;

int N_DEF = 1000;
int N;

// Perform matrix multiplication
void multiply(float A[][10000], float B[][10000], float C[][10000]) {
    // int C[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Display a matrix
void display(float mat[][10000]) {
    for (int i = 0; i < N; i++) {
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
    //                                                   // 
    ///////////////////////////////////////////////////////

    if (argc == 1){
        N = N_DEF;
    }
    else if (argc == 2){
        N = atoi(argv[1]);
    }
    else{
        cout<<"Invalid arguments. Exitting."<<endl;
        exit(1);
    }

    clock_t start, end;
    double  elapsed;

    // Declared as static so that they do not deside in stack & cause segmentation fault
    static float A[10000][10000], B[10000][10000], C[10000][10000];
    
    // Initialize matrices A & B to random floating point values (between 0 & 1)
    
    srand(0);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = rand() / (RAND_MAX * 1.0);
            B[i][j] = rand() / (RAND_MAX * 1.0);
        }
    }

    start = clock();
    multiply(A, B, C);
    end = clock();
    elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf(" \n Time taken is %f \n",elapsed);

}