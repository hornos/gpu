/* This software contains source code provided by NVIDIA Corporation. */

#include <iostream>
#include "mpigpu.h"

extern void abort(int);


__global__ void kernel(real* input, real* output) {
  int tid = blockIdx.x * blockDim.x + threadIdx.x;
  output[tid] = sqrt(input[tid]);
}

void compute(real* hostData, int blockSize, int gridSize) {
  int dataSize = blockSize * gridSize;
  int memsize  = dataSize * sizeof(real);

  // Allocate data on GPU memory
  real* deviceInputData = NULL;
  cudaMalloc((void**)&deviceInputData, memsize);

  real* deviceOutputData = NULL;
  cudaMalloc((void**)&deviceOutputData, memsize);

  // copy to GPU
  cudaMemcpy(deviceInputData, hostData, memsize, cudaMemcpyHostToDevice);

  // Run kernel
  kernel<<<gridSize, blockSize>>>(deviceInputData, deviceOutputData);

  // Copy to CPU
  cudaMemcpy(hostData, deviceOutputData, memsize, cudaMemcpyDeviceToHost);

  cudaFree(deviceInputData);
  cudaFree(deviceOutputData);
}
