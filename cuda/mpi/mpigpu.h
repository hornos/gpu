/* This software contains source code provided by NVIDIA Corporation. */

#include <mpi.h>
#include <cuda.h>

#ifdef KIND_DOUBLE
typedef double real;
#else
typedef float real;
#endif

extern "C" {
void compute(real* hostData, int blockSize, int gridSize);
}
