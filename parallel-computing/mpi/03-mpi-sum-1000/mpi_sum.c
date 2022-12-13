#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* for strcmp */

typedef long int MyLong;

static void print_usage(const char* progname) {
  printf("Usage:\n");
  printf("  %s LAST        # Sum of numbers in range [1, LAST]\n", progname);
  printf("  %s FIRST LAST  # Sum of numbers in range [FIRST,LAST]\n", progname);
}

static void parse_arguments(int argc, char* argv[], int* firstp, int* lastp) {
  int first_val = 1;
  int last_val = 1000;
  if (argc > 1) {
    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
      print_usage(argv[0]);
      exit(1);
    }
    if (argc == 2) {
      last_val = atoi(argv[1]);
    } else if (argc == 3) {
      first_val = atoi(argv[1]);
      last_val = atoi(argv[2]);
    } else {
      print_usage(argv[1]);
      exit(1);
    }
  }

  if (first_val > last_val) {
    printf(
        "Start number must be less than or equal to Last number."
        " However, got Start(%d) > Last(%d)\n",
        first_val, last_val);
    exit(2);
  }
  *firstp = first_val;
  *lastp = last_val;
}

static void determine_range_for_processor(int total_start, int total_last,
                                          int rank, int N, int* start_p,
                                          int* last_p, int* extra) {
  int total_cnt = (total_last - total_start + 1);
  int avg_cnt = total_cnt / N;
  int remainder = total_cnt % N;

  *start_p = total_start + avg_cnt * rank;
  *last_p = *start_p + avg_cnt - 1;
  *extra = rank < remainder ? (total_last - rank) : 0;
}

static MyLong each_processor_compute(int start, int last, int extra) {
  MyLong result = extra;
  while (start < last) {
    result += start + last;
    start++;
    last--;
  }
  if (start == last) {
    result += start;
  }
  return result;
}

int main(int argc, char* argv[]) {
  // Initialize the MPI environment. The two arguments to MPI Init are not
  // currently used by MPI implementations, but are there in case future
  // implementations might need the arguments.
  MPI_Init(NULL, NULL);

  // Get the number of processes
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  // Get the rank of the process
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  // Get the name of the processor
  char processor_name[MPI_MAX_PROCESSOR_NAME];
  int name_len;
  MPI_Get_processor_name(processor_name, &name_len);

  int first_val = 0, last_val = 0;
  parse_arguments(argc, argv, &first_val, &last_val);

  int my_first = 0, my_last = 0, my_extra = 0;
  determine_range_for_processor(first_val, last_val, world_rank, world_size,
                                &my_first, &my_last, &my_extra);

  MyLong my_answer = each_processor_compute(my_first, my_last, my_extra);
  printf("Rank %d/%d from %s, [%d...%d] + [%d]=%ld\n", world_rank, world_size,
         processor_name, my_first, my_last, my_extra, my_answer);
  MyLong final_answer = 0;

  if (world_rank != 0) {
    MPI_Send(
        /* data         = */ &my_answer,
        /* count        = */ 1,
        /* datatype     = */ MPI_LONG,
        /* destination  = */ 0,
        /* tag          = */ 1,
        /* communicator = */ MPI_COMM_WORLD);
  } else {
    for (int j = 1; j < world_size; j++) {
      MyLong received_answer = 0;
      MPI_Recv(
          /* data         = */ &received_answer,
          /* count        = */ 1,
          /* datatype     = */ MPI_LONG,
          /* source       = */ j,
          /* tag          = */ 1,
          /* communicator = */ MPI_COMM_WORLD,
          /* status       = */ MPI_STATUS_IGNORE);
      final_answer += received_answer;
    }
  }

  if (world_rank == 0) {
    final_answer += my_answer;
    printf("Sum of [%d...%d] is %ld\n", first_val, last_val, final_answer);
  }

  // Finalize the MPI environment. No more MPI calls can be made after this
  MPI_Finalize();
}
