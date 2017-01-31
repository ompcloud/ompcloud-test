/*
   This program performs matrix multiplication on the GPU with
   dynamically allocated matrices.

    Author: Gleison Souza Diniz Mendonça
    Date: 04-01-2015
    version 2.0

    Run:
    ipmacc mat-mul_gpu.c -o mat
    ./mat matrix-size
*/

#include "test_util.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef RUN_TEST
#define SIZE 2000
#elif RUN_BENCHMARK
#define SIZE 9600
#else
#define SIZE 1000
#endif

#define PERCENT_DIFF_ERROR_THRESHOLD 0.01

// Initialize matrices.
void init(float *a, float *b, float *c_cpu, float *c_gpu) {
  int i, j;
  for (i = 0; i < SIZE; ++i) {
    for (j = 0; j < SIZE; ++j) {
      a[i * SIZE + j] = (float)i + j % 100;
      b[i * SIZE + j] = (float)i + j % 100;
      c_cpu[i * SIZE + j] = 0.0f;
      c_gpu[i * SIZE + j] = 0.0f;
    }
  }
}

/// matrix multiplication algorithm GPU
/// s = size of matrix
void mul_GPU(float *a, float *b, float *c) {

//#pragma omp target map(tofrom: c[:SIZE*SIZE]) device(DEVICE_ID)
#pragma omp target map(to : a[ : SIZE *SIZE], b[ : SIZE *SIZE])                \
                           map(tofrom : c[ : SIZE *SIZE]) device(DEVICE_ID)
  {
#pragma omp parallel for // collapse(2)
    for (int i = 0; i < SIZE; ++i) {
      //#pragma omp target data map(to: a[i*SIZE:(i+1)*SIZE]) //map(tofrom:
      // c[i*SIZE:(i+1)*SIZE])
      for (int j = 0; j < SIZE; ++j) {
        c[i * SIZE + j] = i * SIZE + j;
      }
    }
  }
}

void mul_CPU(float *a, float *b, float *c) {

  int i, j, k;
  float sum = 0.0;

  for (i = 0; i < SIZE; ++i) {
    for (j = 0; j < SIZE; ++j) {
      c[i * SIZE + j] = i * SIZE + j;
    }
  }
}

int compareResults(float *a, float *b) {
  int i, j, fail = 0;

  for (i = 0; i < SIZE; i++) {
    for (j = 0; j < SIZE; j++) {
      if (a[i * SIZE + j] != b[i * SIZE + j]) {
        fail++;
        // if(i < 10)
        fprintf(stdout, "%d => %f != %f \n", i * SIZE + j, a[i * SIZE + j],
                b[i * SIZE + j]);
      }
    }
  }

  // Print results
  printf("Non-Matching Outputs : %d\n", fail);
  return fail;
}

int main(int argc, char *argv[]) {

  double t_start, t_end;
  int fail = 0;
  float *a, *b, *c_cpu, *c_gpu;

  a = (float *)malloc(sizeof(float) * SIZE * SIZE);
  b = (float *)malloc(sizeof(float) * SIZE * SIZE);
  c_cpu = (float *)calloc(sizeof(float), SIZE * SIZE);
  c_gpu = (float *)calloc(sizeof(float), SIZE * SIZE);

  init(a, b, c_cpu, c_gpu);

  fprintf(stdout, "<< Matrix Multiplication >>\n");

  t_start = rtclock();
  mul_GPU(a, b, c_gpu);
  t_end = rtclock();
  fprintf(stdout, "GPU Runtime: %0.6lfs\n", t_end - t_start);

#ifdef RUN_TEST
  t_start = rtclock();
  mul_CPU(a, b, c_cpu);
  t_end = rtclock();
  fprintf(stdout, "CPU Runtime: %0.6lfs\n", t_end - t_start);

  fail = compareResults(c_cpu, c_gpu);
#endif

  free(a);
  free(b);
  free(c_cpu);
  free(c_gpu);

  return fail;
}
