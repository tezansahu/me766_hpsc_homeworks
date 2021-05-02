#define N 1000

#include <stdio.h>
#include <time.h>
#include "cuda_runtime.h"

void initialize(float A[N][N], float B[N][N]) {
    srand(0);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = rand() / (RAND_MAX * 1.0);
            B[i][j] = rand() / (RAND_MAX * 1.0);
        }
    }
}

void display(float mat[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%.2f\t", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


__global__ void matMul(float *A, float *B, float *C) {
    int block = blockIdx.x;     // Used to index row of matrix
    int thread = threadIdx.x;   // Used to index column of matrix
    
    int dim = blockDim.x;

    float sum = 0;
    for(int i = 0; i < N; i++){
        sum += A[block*dim + i] * B[i*dim + thread];
    }

    C[block*dim + thread] = sum;
}


int main(int argc, char **argv) {
    float A[N][N], B[N][N], C[N][N];

    clock_t start, end;
    double  elapsed;

    float *dev_A, *dev_B, *dev_C;
    int size = N*N*sizeof(float);
    
    cudaMalloc((void **)&dev_A, size);
    cudaMalloc((void **)&dev_B, size);
    cudaMalloc((void **)&dev_C, size);

    initialize(A, B);

    start = clock();

    // Copy inputs from host to device
    cudaMemcpy(dev_A, A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(dev_B, B, size, cudaMemcpyHostToDevice);

    // Launch the Matrix multiplication kernel
    matMul<<<N, N>>>(dev_A, dev_B, dev_C);

    // Copy result from device to host
    cudaMemcpy(C, dev_C, size, cudaMemcpyDeviceToHost);

    end = clock();
    elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;

    // display(A);
    // display(B);
    // display(C);

    printf(" \n Time taken is %f \n",elapsed);

    cudaFree(dev_A);
    cudaFree(dev_B);
    cudaFree(dev_C);
}
