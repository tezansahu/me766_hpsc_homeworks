#include <iostream>
#include <chrono>
#include <math.h>
#include <stdio.h>
#include <mpi.h>

#define MAP 101         // Tag for messages mapping rows from master to worker nodes
#define GATHER 102      // Tag for messages gathering computed results from worker nodes to master

using namespace std;

int N_DEF = 1000;
int DEFAULT_NUM_PES = 1;

int N;
int num_pes;
int i, j, k;
MPI_Status status;

// Initialize matrices A & B to random floating point values (between 0 & 1)
void init_matrices(float A[][10000], float B[][10000]) {
    srand(0);
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            A[i][j] = rand() / (RAND_MAX * 1.0);
            B[i][j] = rand() / (RAND_MAX * 1.0);
        }
    }
}

// Display a matrix
void display(float *mat) {
    for (i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%.2f\t", *((mat + i*N) + j));
        }
        printf("\n");
    }
    printf("\n");
}


int main(int argc, char **argv) {
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

    int my_pe, offset, rows;
    chrono::duration<double> elapsed_seconds;

    float A[N][N], B[N][N], C[N][N];

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &num_pes);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_pe);

    // printf("Hello from %d\n", my_pe);
    

    // Let PE 0 be the master node, which initializes the matrices & later sends the matrix data to other worker nodes for multiplication
    if (my_pe == 0) {
        // printf("Hi");
        // Initialize the matrices
        srand(0);
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                A[i][j] = rand() / (RAND_MAX * 1.0);
                B[i][j] = rand() / (RAND_MAX * 1.0);
            }
        }

        // display((float *)A);
        // display((float *)B);

        offset = 0;
        rows = N/(num_pes - 1);

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////// Matrix Multiplication //////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        auto start_mul = chrono::system_clock::now();

        // Send the data for a set of rows to the corresponding workers
        for (i = 1; i < num_pes; i++) {
            // The last worker node takes care of rows that may be left out in case N is not divisible by number of workers
            if (i == num_pes - 1) {
                rows += N % (num_pes - 1);
            }

            MPI_Send(&offset, 1, MPI_INT, i, MAP, MPI_COMM_WORLD);
            MPI_Send(&rows, 1, MPI_INT, i, MAP, MPI_COMM_WORLD);
            MPI_Send(&A[offset][0], rows*N, MPI_FLOAT, i, MAP, MPI_COMM_WORLD);
            MPI_Send(&B[0][0], N*N, MPI_FLOAT, i, MAP, MPI_COMM_WORLD);

            offset += rows;
        }

        rows = N/(num_pes - 1);

        // Receive the results from workers
        for (i = 1; i < num_pes; i++) {
            // The last worker node takes care of rows that may be left out in case N is not divisible by number of workers
            if (i == num_pes - 1) {
                rows += N % (num_pes - 1);
            }

            MPI_Recv(&offset, 1, MPI_INT, i, GATHER, MPI_COMM_WORLD, &status);
            MPI_Recv(&rows, 1, MPI_INT, i, GATHER, MPI_COMM_WORLD, &status);
            MPI_Recv(&C[offset][0], rows*N, MPI_FLOAT, i, GATHER, MPI_COMM_WORLD, &status);
        }

        auto end_mul = chrono::system_clock::now();
        elapsed_seconds = end_mul - start_mul;
        printf("Matrix Multiplication: \t\t %.3f s\n", elapsed_seconds.count());

        // display((float *)C);
    }

    else {
        MPI_Recv(&offset, 1, MPI_INT, 0, MAP, MPI_COMM_WORLD, &status);
        MPI_Recv(&rows, 1, MPI_INT, 0, MAP, MPI_COMM_WORLD, &status);
        MPI_Recv(&A, rows*N, MPI_FLOAT, 0, MAP, MPI_COMM_WORLD, &status);
        MPI_Recv(&B, N*N, MPI_FLOAT, 0, MAP, MPI_COMM_WORLD, &status);

        // Actual multiplication being carried out by the worker nodes
        for (i = 0; i < rows; i++) {
            for (j = 0; j < N; j++) {
                C[i][j] = 0;
                for (k = 0; k < N; k++) {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }

        MPI_Send(&offset, 1, MPI_INT, 0, GATHER, MPI_COMM_WORLD);
        MPI_Send(&rows, 1, MPI_INT, 0, GATHER, MPI_COMM_WORLD);
        MPI_Send(&C, rows*N, MPI_FLOAT, 0, GATHER, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    
}