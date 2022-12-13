#ifndef MPI_MATRIX_MULT_MATMULT_BY_MPI_H_
#define MPI_MATRIX_MULT_MATMULT_BY_MPI_H_

#include <mpi.h>

typedef struct _MatrixMultContext {
  int numprocs;
  int dimension;       /* matrix dimension */
  int my_rank;         /* my_id */
  const char* my_name; /* my processor name */
} MatrixMultContext;

int matmult_by_mpi(const MatrixMultContext* ctx, double* my_result);

#endif  // MPI_MATRIX_MULT_MATMULT_BY_MPI_H_
