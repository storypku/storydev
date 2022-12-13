#ifndef MPI_MATRIX_MULT_MPI_COMPLEX_EXT_H_
#define MPI_MATRIX_MULT_MPI_COMPLEX_EXT_H_

#include <mpi.h>

#include "complex.h"

/**
 * Ref: https://computing.llnl.gov/tutorials/mpi/samples/C/mpi_struct.c
 * */
/**
 * Since c has no native MPI_COMPLEX support like Fortran, we have to "register"
 * Our complex_t type to enable MPI_Send/Recv.
 */
int mpi_register_complex(MPI_Datatype* mpi_complex_t);

/* Call this before MPI_Finalize() */
int mpi_deregister_complex(MPI_Datatype* mpi_complex_t);

#endif  // MPI_MATRIX_MULT_MPI_COMPLEX_EXT_H_
