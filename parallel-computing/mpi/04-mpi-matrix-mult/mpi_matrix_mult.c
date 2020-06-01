/* TODO: Fox's algorithm to multiply two square matrices
 * https://notendur.hi.is/hh/kennsla/hpc/fox.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matmult_by_mpi.h"
#include "matrix_helper.h"

static void print_usage(const char *progname) {
  printf("Usage:\n");
  printf("  %s -h|--help  Show this message\n", progname);
  printf(
      "  %s [number]   Use matrix dimension specified "
      "by \"number\", DEFAULT: 100.\n",
      progname);
}

static void check_arguments_n_determine_dimension(int argc, char *argv[],
                                                  int numprocs, int *dim_p) {
  if (argc > 2) {
    print_usage(argv[0]);
    exit(1);
  }

  int dimension = N;
  if (argc == 2) {
    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
      print_usage(argv[0]);
      exit(1);
    }
    dimension = atoi(argv[1]);
    if (dimension <= 0) {
      printf(
          "Oops, the matrix dimension you specified (N=%d) "
          "is illegal. Use default (N=100).\n",
          dimension);
      dimension = N;
    }
  }
  if (dimension % numprocs != 0) {
    printf(
        "Oops, matrix dimension (N=%d) can't be divided equally "
        "among %d processors, exit...\n",
        dimension, numprocs);
    exit(2);
  }
  *dim_p = dimension;
}

int main(int argc, char *argv[]) {
  // Initialize the MPI environment. The two arguments to MPI Init are not
  // currently used by MPI implementations, but are there in case future
  // implementations might need the arguments.
  MPI_Init(NULL, NULL);

  // Get the number of processes
  int numprocs;
  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

  // Get the rank of the process
  int myid;
  MPI_Comm_rank(MPI_COMM_WORLD, &myid);

  // Get the name of the processor
  char processor_name[MPI_MAX_PROCESSOR_NAME];
  int name_len;
  MPI_Get_processor_name(processor_name, &name_len);

  int dimension = N;
  check_arguments_n_determine_dimension(argc, argv, numprocs, &dimension);
  // MPI_Barrier(MPI_COMM_WORLD);

  double start_time_ms = 0.0;
  if (myid == 0) {
    start_time_ms = MPI_Wtime() * 1000;
  }
  MatrixMultContext my_ctx = {.numprocs = numprocs,
                              .dimension = dimension,
                              .my_rank = myid,
                              .my_name = processor_name};

  double my_result = 0;
  matmult_by_mpi(&my_ctx, &my_result);

  double final_result = 0.0;

  if (myid != 0) {
    MPI_Send(
        /* data         = */ &my_result,
        /* count        = */ 1,
        /* datatype     = */ MPI_DOUBLE,
        /* destination  = */ 0,
        /* tag          = */ 1,
        /* communicator = */ MPI_COMM_WORLD);
  } else {
    final_result = my_result;
    for (int j = 1; j < numprocs; j++) {
      double received_result = 0;
      MPI_Recv(
          /* data         = */ &received_result,
          /* count        = */ 1,
          /* datatype     = */ MPI_DOUBLE,
          /* source       = */ j,
          /* tag          = */ 1,
          /* communicator = */ MPI_COMM_WORLD,
          /* status       = */ MPI_STATUS_IGNORE);
      final_result += received_result;
    }
    final_result = final_result / dimension / dimension;
  }

  if (myid == 0) {
    double end_time_ms = MPI_Wtime() * 1000;
    double time_delta_ms = end_time_ms - start_time_ms;
    printf("S=%.6lf for matrix of (%d)X(%d), time cost: %.3lf ms\n",
           final_result, dimension, dimension, time_delta_ms);
  }

  // Finalize the MPI environment. No more MPI calls can be made after this
  MPI_Finalize();
}
