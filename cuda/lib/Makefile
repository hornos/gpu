.SUFFIXES: .F .f90 .c .cpp

include ../arch.make

C_SRC   = acc_cuda.cpp par_mpi.cpp
C_OBJ   = $(C_SRC:.cpp=.o)
LIB     = paracc.a
LDFLAGS = $(LIB) -L$(CUDA_LIB) -lcudart

F_SRC  = $(C_SRC:.c=.F)
F_MOD  = $(F_SRC:.F=.mod)

all: $(LIB) test

$(LIB): $(C_OBJ)
	ar vq $(LIB) $(C_OBJ)

test: test.cpp $(LIB)
	$(MPICXX) -c $(CFLAGS) -o test.o test.cpp
	$(MPICXX) -o test test.o $(LIB)

.c.o:
	$(CC) -c $(CFLAGS) $< -o $@

.cpp.o:
	$(CXX) -c $(CFLAGS) $< -o $@

.F.o:
	$(CPP)
	$(FC) $(FFLAGS) -c $*.f90 -o $@

.F.mod:
	$(CPP)
	$(FC) $(FFLAGS) -c $*.f90

clean:
	rm -f *.o *.a *.mod *.f90
