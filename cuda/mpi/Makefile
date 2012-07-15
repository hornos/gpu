.SUFFIXES: .c .cpp .cu

include ../arch.make

EXE = mpigpu
PARACC = ../lib/paracc.a

CPP_SRC = mpigpu.cpp
CPP_OBJ = $(CPP_SRC:.cpp=.o)
CUS_SRC = kernel.cu
CUS_OBJ = $(CUS_SRC:.cu=.o)

LDFLAGS = $(PARACC) -L$(CUDA_LIB) -lcudart

all: $(EXE)

$(EXE): $(CPP_OBJ) $(CUS_OBJ)
	$(MPICXX) -o $(EXE) $(CPP_OBJ) $(CUS_OBJ) $(LDFLAGS)

.c.o:
	$(CC) -c $(CFLAGS) $< -o $@

.cu.o:
	$(NVCC) -arch $(ARCH) -c $(CFLAGS) $< -o $@

.cpp.o:
	$(MPICXX) -c $(CFLAGS) $< -o $@

clean:
	rm -f *.o *.a *.mod *.f90
