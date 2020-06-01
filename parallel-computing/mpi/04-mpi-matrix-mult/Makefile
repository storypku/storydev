.PHONY: clean all mpi_run

MPICC = mpicc
CC = gcc

EXECUTABLES = mpi_matrix_mult ordinary_matrix_mult

# The CFLAGS variable sets compile flags for gcc:
#  -Wall       give verbose compiler warnings
#  -O2         optimize generated code with level 2
#  -std=gnu99  use the GNU99 standard language definition
CFLAGS = -Wall -O2 -std=gnu99

# Controls whether we should use REAL or COMPLEX mode for matrix B
DEFINES = -DNOMAT_B_IS_COMPLEX
# DEFINES = -DMAT_B_IS_COMPLEX

INCLUDE_FLAGS = -I.
LD_FLAGS = -lm

HEADERS = complex.h mpi_complex_ext.h matrix_helper.h matmult_by_mpi.h
SRCS = complex.c mpi_complex_ext.c matrix_helper.c matmult_by_mpi.c mpi_matrix_mult.c

ORDINARY_HDRS = complex.h matrix_helper.h
ORDINARY_SRCS = complex.c matrix_helper.c ordinary_matrix_mult.c

all: ${EXECUTABLES}

mpi_matrix_mult: ${SRCS} ${HEADERS}
	@echo "Compiling mpi_matrix_mult ..."
	$(MPICC) -o $@ ${SRCS} $(CFLAGS) $(DEFINES) $(INCLUDE_FLAGS) $(LD_FLAGS)

ordinary_matrix_mult: ${ORDINARY_SRCS} ${ORDINARY_HDRS}
	@echo "Compiling ordinary_matrix_mult ..."
	$(CC) -o $@ ${ORDINARY_SRCS} $(CFLAGS) $(DEFINES) $(INCLUDE_FLAGS) $(LD_FLAGS)

clean:
	@rm -f ${EXECUTABLES}

mpi_run: mpi_matrix_mult
	mpirun -n 10 ./mpi_matrix_mult
