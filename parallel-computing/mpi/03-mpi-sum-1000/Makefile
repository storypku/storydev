.PHONY: clean all mpi_run
MPICC = mpicc

EXECUTABLES = mpi_sum mpi_sum_opt

# The CFLAGS variable sets compile flags for gcc:
#  -Wall       give verbose compiler warnings
#  -O2         optimize generated code
#  -std=gnu99  use the GNU99 standard language definition
CFLAGS = -Wall -O2 -std=gnu99

all: ${EXECUTABLES}

mpi_sum: mpi_sum.c
	@echo "Compiling mpi_sum ..."
	$(MPICC) -o $@ $< $(CFLAGS)

mpi_sum_opt: mpi_sum_opt.c
	@echo "Compiling mpi_sum_opt ..."
	$(MPICC) -o $@ $< $(CFLAGS)

clean:
	@rm -f ${EXECUTABLES}

mpi_run: mpi_sum_opt
	mpirun -n 10 ./mpi_sum_opt
