#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <iostream>
#include <ctime>
using namespace std;


void matrix_gen(int size, double **matrix){
    srand(time(0));
    for(int i = 0; i < size; ++i)
        matrix[i] = new double[size];
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = (int)((double)rand()/RAND_MAX*15) + 1;
        }
    }

}

void do_job_one(double **A, int size) {
    double *Res = new double[size];
    int i, j;
    #pragma omp parallel private(i, j)
    {
        int iters = 0;
        #pragma omp for schedule(dynamic, 4)
        for (i = 0; i < size; i++) {
//            printf("The value n in the thread %d: %d\n", omp_get_thread_num(), i);
            int max = A[i][0];
            for (j = 1; j < size; j++) {
                if (A[i][j] < max)
                {
                    max = A[i][j];
                }
            }
            Res[i] = max;
//            cout << Res[i] << endl; Res
            iters++;
        }
        #pragma omp critical
        printf("Thread %d did %d iterations\n", omp_get_thread_num(), iters);
    }

}

void do_job_two(double **A, int size) {
    double *Res = new double[size];
    int i, j;
#pragma omp parallel private(i, j)
    {
        int iters = 0;
#pragma omp for schedule(static, 4)
        for (i = 0; i < size; i++) {
//            printf("The value n in the thread %d: %d\n", omp_get_thread_num(), i);
            int max = A[i][0];
            for (j = 1; j < size; j++) {
                if (A[i][j] < max)
                {
                    max = A[i][j];
                }
            }
            Res[i] = max;
//            cout << Res[i] << endl; Res
            iters++;
        }
#pragma omp critical
        printf("Thread %d did %d iterations\n", omp_get_thread_num(), iters);
    }

}

int main()
{
    int sz = 1000, rows = sz, columns = sz;
    double **matrixA = new double*[sz];
    double **matrixB = new double*[sz];

    matrix_gen(sz, matrixA);
    matrix_gen(sz, matrixB);

    printf("Matrix A result: \n");
    do_job_one(matrixA, sz);
    printf("Matrix B result: \n");
    do_job_two(matrixB, sz);


    free(matrixA);
    free(matrixB);
    return 0;
}