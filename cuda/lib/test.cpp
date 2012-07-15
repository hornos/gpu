#include <iostream>
#include "par_mpi.h"

int main( int argc, char **argv ) {
  int comm[2];
  par::mpiInit( &argc, &argv );
  par::mpiWorld( comm );
  par::mpiInfo( comm );
  par::mpiStop();
}
