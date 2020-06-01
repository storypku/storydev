#include "mpi_complex_ext.h"

/**
 * Ref: https://computing.llnl.gov/tutorials/mpi/samples/C/mpi_struct.c
 * */
/* Call this before use */
int mpi_register_complex(MPI_Datatype *mpi_complex_t) {
  MPI_Datatype plane_types[1];
  int block_counts[1];
  /* MPI_Aint type used to be consistent with syntax of */
  /* MPI_Type_extent routine */
  MPI_Aint offsets[1];
  /* Setup description of the 2 MPI_DOUBLE fields: re, im */
  offsets[0] = 0;
  plane_types[0] = MPI_DOUBLE;
  block_counts[0] = 2;
  /* Now define structured type and commit it */
  MPI_Type_struct(1, block_counts, offsets, plane_types, mpi_complex_t);
  MPI_Type_commit(mpi_complex_t);
  return 0;
}

/* Call this before MPI_Finalize() */
int mpi_deregister_complex(MPI_Datatype *mpi_complex_t) {
  MPI_Type_free(mpi_complex_t);
  return 0;
}
