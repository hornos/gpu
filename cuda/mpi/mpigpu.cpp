/* This software contains source code provided by NVIDIA Corporation. */

#include <iostream>
#include <cstdlib>

#include "par_mpi.h"
#include "acc_cuda.h"
#include "mpigpu.h"

namespace mpigpu
{

void initData( real* data, int size ) {
  for(int i = 0; i < size; i++) {
    data[i] = (real)rand() / RAND_MAX;
  }
}

real sumData( real* data, int size) {
  real accum = (real)0.0;
  for(int i = 0; i < size; i++)
    accum += data[i];
  return accum;
}

} // end namespace mpigpu


void abort(int err) {
  par::mpiAbort(err);
}

int main(int argc, char** argv ) {
  // arguments
  int block = 256;
  int grid  = 10000;
  if( argc > 1 )
    grid  = std::atoi( argv[1] );
  if( argc > 2 )
    block = std::atoi( argv[2] );

  int comm[2];
  par::mpiInit( &argc, &argv );
  par::mpiWorld( comm );

  int pernode = grid * block;
  int total = pernode * comm[1];
  real* dataRoot = NULL;

  par::mpiInfo( comm );
  MPI_MASTER( comm ) {
    std::cout << "Data grid size is " << grid << " with " << block << " blocks" << std::endl;
    // random data for distribution
    dataRoot = new real[total];
    mpigpu::initData( dataRoot, total );
    // check gpus
    //acc::cudaInfo();
  }

  // round-robin select gpus
  acc::cudaDevice( comm );
  // per node data
  acc::cudaNodeInfo( comm );

  real* dataNode = new real[pernode];

  // mpi distribute

#ifdef KIND_DOUBLE
  MPI_Scatter(dataRoot,pernode,MPI_DOUBLE,dataNode,pernode,MPI_DOUBLE,0,MPI_COMM_WORLD);
#else
  MPI_Scatter(dataRoot,pernode,MPI_FLOAT,dataNode,pernode,MPI_FLOAT,0,MPI_COMM_WORLD);
#endif

  MPI_MASTER(comm) {
    delete [] dataRoot;
  }

  // begin work
  compute(dataNode, block, grid);

  real sumNode = mpigpu::sumData( dataNode, pernode );
  real sumRoot;

#ifdef KIND_DOUBLE
  MPI_Reduce(&sumNode,&sumRoot,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
#else
  MPI_Reduce(&sumNode,&sumRoot,1,MPI_FLOAT,MPI_SUM,0,MPI_COMM_WORLD);
#endif
  // end work

  MPI_MASTER(comm) {
    real average = sumRoot / total;
    std::cout << "Average of square roots is: " << average << std::endl;
  }

  delete [] dataNode;
  MPI_Finalize();
  return 0;
}
