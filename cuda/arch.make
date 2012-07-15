CPP = gcc -E -P -C $*.F >$*.f90
FC  = ifort
CC  = icc
CXX = icpc
NVCC = nvcc
MPICXX = mpiicxx

DEFS = -DKIND_DOUBLE

CUDA_LIB = $(CUDA_HOME)/lib64
CFLAGS   = $(DEFS) -I../lib -I$(CUDA_HOME)/include -I$(MPI_ROOT)/include
FFLAGS   = -ffree-form -g -O0 

ARCH = sm_20
