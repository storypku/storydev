#include "matmult_by_mpi.h"

#include <stdio.h>
#include <stdlib.h>

#include "complex.h"
#include "matrix_helper.h"

/**
 * Generalize to cases where elements in matrix B is complex numbers
 * rather than real ones.
 */
#ifdef MAT_B_IS_COMPLEX
#include "mpi_complex_ext.h"
#endif

/* *
 * typedef struct _MatrixMultContext {
 *    int numprocs;
 *    int dimension; // matrix dimension
 *    int my_rank;  // my_id
 *    const char* my_name; // my processor name
 * } MatrixMultContext;
 * */
static int matmult_by_mpi_impl(const MatrixMultContext* ctx,
                               const complex_t* mat_a,
#ifdef MAT_B_IS_COMPLEX
                               const complex_t* mat_b,
#else
                               const double* mat_b,
#endif
                               complex_t* mat_c) {

  const int dim = ctx->dimension;
  int block_size = dim / ctx->numprocs;
  int my_id = ctx->my_rank;

  // step 0: each process performs own calc
  for (int i = 0; i < block_size; i++) {
    const complex_t* array_a = mat_a + i * dim;
    complex_t* array_c = mat_c + i * dim;

    for (int j = my_id * block_size; j < (my_id + 1) * block_size; j++) {
#ifdef MAT_B_IS_COMPLEX
      const complex_t* array_b = mat_b + (j % block_size) * dim;
#else
      const double* array_b = mat_b + (j % block_size) * dim;
#endif
      for (int k = 0; k < dim; k++) {
        /* array_c[j] += array_a[k] * array_b[k]; */
        c_self_add_ab_product(array_a + k, array_b + k, array_c + j);
      }
    }
  }

#ifdef MAT_B_IS_COMPLEX
  complex_t* mat_recv_b =
      (complex_t*)malloc(block_size * dim * sizeof(complex_t));
#else
  double* mat_recv_b = (double*)malloc(block_size * dim * sizeof(double));
#endif

#ifdef MAT_B_IS_COMPLEX
  MPI_Datatype mpi_complex_t;
  mpi_register_complex(&mpi_complex_t);
#endif

  for (int step = 1; step < ctx->numprocs; step++) {
    int id_send = (my_id + step) % ctx->numprocs;
    int id_recv = (ctx->numprocs + my_id - step) % ctx->numprocs;
    // Send/Recv deadlock:
    MPI_Sendrecv(
        /* send data = */ (void*)mat_b,
        /* count     = */ block_size * dim,
#ifdef MAT_B_IS_COMPLEX
        /* datatype  = */ mpi_complex_t,
#else
        /* datatype  = */ MPI_DOUBLE,
#endif
        /* dest      = */ id_send,
        /* send tag  = */ 1,
        /* recv data = */ mat_recv_b,
        /* count     = */ block_size * dim,
#ifdef MAT_B_IS_COMPLEX
        /* datatype  = */ mpi_complex_t,
#else
        /* datatype  = */ MPI_DOUBLE,
#endif
        /* source    = */ id_recv,
        /* tag       = */ 1,
        /* MPI_Comm  = */ MPI_COMM_WORLD,
        /* status    = */ MPI_STATUS_IGNORE);

    /* Disabled the following as I may cause deadlocks when, e.g. P = 2*/
    // MPI_Send(
    //    /* data         = */ mat_b,
    //    /* count        = */ block_size * dim,
    // #ifdef MAT_B_IS_COMPLEX
    //    /* datatype  = */ mpi_complex_t,
    // #else
    //    /* datatype  = */ MPI_DOUBLE,
    // #endif
    //    /* destination  = */ id_send,
    //    /* tag          = */ 1,
    //    /* communicator = */ MPI_COMM_WORLD);
    // MPI_Recv(
    //    /* data         = */ mat_recv_b,
    //    /* count        = */ block_size * dim,
    // #ifdef MAT_B_IS_COMPLEX
    //    /* datatype  = */ mpi_complex_t,
    // #else
    //    /* datatype  = */ MPI_DOUBLE,
    // #endif
    //    /* source       = */ id_recv,
    //    /* tag          = */ 1,
    //    /* communicator = */ MPI_COMM_WORLD,
    //    /* status       = */ MPI_STATUS_IGNORE);
    for (int i = 0; i < block_size; i++) {
      const complex_t* array_a = mat_a + i * dim;
      complex_t* array_c = mat_c + i * dim;

      for (int j = id_recv * block_size; j < (id_recv + 1) * block_size; j++) {
#ifdef MAT_B_IS_COMPLEX
        const complex_t* array_recv_b = mat_recv_b + (j % block_size) * dim;
#else
        const double* array_recv_b = mat_recv_b + (j % block_size) * dim;
#endif
        for (int k = 0; k < dim; k++) {
          c_self_add_ab_product(array_a + k, array_recv_b + k, array_c + j);
        }
      }
    }
  }

#ifdef MAT_B_IS_COMPLEX
  free(mat_recv_b);
  mpi_deregister_complex(&mpi_complex_t);
#endif
  return 0;
}

int matmult_by_mpi(const MatrixMultContext* ctx, double* my_result) {
  if (ctx == NULL || my_result == NULL) {
    return -1;
  }

  int dim = ctx->dimension;
  int block_size = dim / ctx->numprocs;  // B = N / P
  int bytes_count = block_size * dim * sizeof(complex_t);

  complex_t* my_mat_a = (complex_t*)malloc(bytes_count);
#ifdef MAT_B_IS_COMPLEX
  complex_t* my_mat_b = (complex_t*)malloc(bytes_count);
#else
  double* my_mat_b = (double*)malloc(block_size * dim * sizeof(double));
#endif

  complex_t* my_mat_c = (complex_t*)calloc(block_size * dim, sizeof(complex_t));

  for (int i = 0; i < block_size; i++) {
    int row = ctx->my_rank * block_size + i;
    complex_t* address = my_mat_a + i * dim;
    set_elements_of_row_for_mat_a(row, dim, address);
  }

  for (int j = 0; j < block_size; j++) {
    int col = ctx->my_rank * block_size + j;
#ifdef MAT_B_IS_COMPLEX
    complex_t* address = my_mat_b + j * dim;
#else
    double* address = my_mat_b + j * dim;
#endif
    set_elements_of_col_for_mat_b(col, dim, address);
  }

  matmult_by_mpi_impl(ctx, my_mat_a, my_mat_b, my_mat_c);

  free(my_mat_a);
  free(my_mat_b);

  double my_s = 0.0;
  for (int i = 0; i < block_size; i++) {
    double row_s = 0.0;
    complex_t* address = my_mat_c + i * dim;
    calc_sum_of_modulus_square_of_row_for_mat_c(address, dim, &row_s);
    my_s += row_s;
  }

  free(my_mat_c);
  *my_result = my_s;
  return 0;
}
