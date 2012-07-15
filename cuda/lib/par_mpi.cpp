#include <iostream>
#include <mpi.h>
#include "par_mpi.h"

namespace par
{

int mpiInit( int *argc, char ***argv ) {
  return MPI_Init( argc, argv );
}

int mpiWorld( int comm[2] ) {
  int ret;
  ret  = MPI_Comm_rank(MPI_COMM_WORLD, &(comm[0]) );
  ret += MPI_Comm_size(MPI_COMM_WORLD, &(comm[1]) );
  return ret;
}

void mpiInfo( int comm[2] ) {
  MPI_MASTER( comm ) {
    std::cout << "MPI Running on " << comm[1] << " nodes" << std::endl;
  }
}

void mpiStop( void ) {
  MPI_Finalize();
}

void mpiAbort(int err) {
  MPI_Abort(MPI_COMM_WORLD, err);
}
}
