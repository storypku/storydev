#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "complex.h"
#include "matrix_helper.h"  // N

int main(int argc, char *argv[]) {
  int dim = N;
  if (argc == 2) {
    dim = atoi(argv[1]);
  }

  struct timeval start_tv, end_tv;
  gettimeofday(&start_tv, NULL);

  complex_t *mat_a = (complex_t *)malloc(dim * dim * sizeof(complex_t));
#ifdef MAT_B_IS_COMPLEX
  complex_t *mat_b = (complex_t *)malloc(dim * dim * sizeof(complex_t));
#else
  double *mat_b = (double *)malloc(dim * dim * sizeof(double));
#endif

  complex_t *mat_c = (complex_t *)calloc(dim * dim, sizeof(complex_t));

  for (int i = 0; i < dim; i++) {
    set_elements_of_row_for_mat_a(i, dim, mat_a + i * dim);
  }

  for (int j = 0; j < dim; j++) {
    set_elements_of_col_for_mat_b(j, dim, mat_b + j * dim);
  }

  for (int i = 0; i < dim; i++) {
    complex_t *array_a = mat_a + i * dim;
    complex_t *array_c = mat_c + i * dim;
    for (int j = 0; j < dim; j++) {
#ifdef MAT_B_IS_COMPLEX
      complex_t *array_b = mat_b + j * dim;
#else
      double *array_b = mat_b + j * dim;
#endif
      for (int k = 0; k < dim; k++) {
        c_self_add_ab_product(array_a + k, array_b + k, array_c + j);
      }
    }
  }
  free(mat_a);
  free(mat_b);

  double result = 0.0;
  for (int i = 0; i < dim; i++) {
    double row_s = 0.0;
    const complex_t *array_c = mat_c + i * dim;
    calc_sum_of_modulus_square_of_row_for_mat_c(array_c, dim, &row_s);
    result += row_s;
  }
  result /= dim * dim;
  free(mat_c);

  gettimeofday(&end_tv, NULL);
  double time_delta_ms = (end_tv.tv_sec - start_tv.tv_sec) * 1000 +
                         (end_tv.tv_usec - start_tv.tv_usec) / 1000.0;

  printf("S=%.6lf for matrix of (%d)X(%d), time cost: %.3lf ms\n", result, dim,
         dim, time_delta_ms);

  return 0;
}
