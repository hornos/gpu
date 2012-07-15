/* This software contains source code provided by NVIDIA Corporation. */
#include <mpi.h>
#include <iostream>

#define MPI_IONODE 0
#define MPI_MASTER(rank) if(rank[0]==MPI_IONODE)

namespace par
{
int mpiInit( int*, char*** );
int mpiWorld( int[] );
void mpiInfo( int[] );
void mpiStop( void );
void mpiAbort( int );
}
