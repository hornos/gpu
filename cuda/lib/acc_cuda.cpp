/* This software contains source code provided by NVIDIA Corporation. */

#include <stdio.h>
#include <cuda.h>
#include <cuda_runtime_api.h>

#include "acc_cuda.h"

namespace acc
{

int cudaDevice( int rank[2] ) {
  return cudaSetDevice( rank[0] % rank[1] );
}

void cudaNodeInfo( int rank[2] ) {
  cudaDeviceProp prop;
  cudaGetDeviceProperties( &prop, rank[0] ); 
  printf( "[%3d] Name: %s (%d.%d.%d)\n", rank[0], prop.name, prop.pciBusID, prop.pciDeviceID, prop.pciDomainID );
}

void cudaInfo( void ) {
  cudaDeviceProp prop;
  int count;
  int i;
  cudaGetDeviceCount( &count );
  for (i=0; i< count; i++) {
    cudaGetDeviceProperties( &prop, i ); 
    printf( "--- General Information for device %d\n", i );
    printf( "Name: %s\n", prop.name );
    printf( "Compute capability: %d.%d\n", prop.major, prop.minor );
    printf( "Clock rate: %d\n", prop.clockRate );
    printf( "Device copy overlap: " );
    if (prop.deviceOverlap) printf( "Enabled\n" );
    else printf( "Disabled\n" );
    printf( "Kernel execition timeout : " );
    if (prop.kernelExecTimeoutEnabled) printf( "Enabled\n" );
    else printf( "Disabled\n" );
    printf( "--- Memory Information for device %d\n", i );
    printf( "Total global mem: %ld\n", prop.totalGlobalMem );
    printf( "Total constant Mem: %ld\n", prop.totalConstMem );
    printf( "Max mem pitch: %ld\n", prop.memPitch );
    printf( "Texture Alignment: %ld\n", prop.textureAlignment );
    printf( "--- MP Information for device %d\n", i );
    printf( "Multiprocessor count: %d\n",prop.multiProcessorCount );
    printf( "Shared mem per mp: %ld\n", prop.sharedMemPerBlock );
    printf( "Registers per mp: %d\n", prop.regsPerBlock );
    printf( "Threads in warp: %d\n", prop.warpSize );
    printf( "Max threads per block: %d\n",prop.maxThreadsPerBlock );
    printf( "Max thread dimensions: (%d, %d, %d)\n",prop.maxThreadsDim[0],prop.maxThreadsDim[1],prop.maxThreadsDim[2] );
    printf( "Max grid dimensions: (%d, %d, %d)\n",prop.maxGridSize[0], prop.maxGridSize[1],prop.maxGridSize[2] );
    printf( "\n" );
  }
}

}
