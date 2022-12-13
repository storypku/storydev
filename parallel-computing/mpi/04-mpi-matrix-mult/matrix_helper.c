#include "matrix_helper.h"

#include <math.h>

#include "complex.h"

#define X(i, dim) ((i - 1) * 1.0 / ((dim)-1))
#define Y(j, dim) ((j - 1) * 1.0 / ((dim)-1))

/* Set elements of a's i-th row */
void set_elements_of_row_for_mat_a(int i, int dim, complex_t* a) {
  if (a == NULL) {
    return;
  }
  double xi = X(i, dim);
  double factor = sin(3 * xi);

  for (int j = 0; j < dim; j++) {
    double yj = Y(j, dim);
    /* Aij=sin(3xi)*e^(yj) */
    (a + j)->re = factor * cos(yj);
    (a + j)->im = factor * sin(yj);
  }
}

/* Set elements of b's j-th column */
void set_elements_of_col_for_mat_b(int j, int dim,
#ifdef MAT_B_IS_COMPLEX
                                   complex_t* b
#else
                                   double* b
#endif
) {
  if (b == NULL) {
    return;
  }
  double yj = Y(j, dim);
  for (int i = 0; i < dim; i++) {
    double xi = X(i, dim);
    /* Bij = (xi + cos(4xi)) * (1+yi) */
    double real = (xi + cos(4 * xi)) * (1 + yj);
#ifdef MAT_B_IS_COMPLEX
    b[i].re = real;
    b[i].im = 0.0;
#else
    *b = real;
#endif
  }
}

int calc_sum_of_modulus_square_of_row_for_mat_c(const complex_t* c, int dim,
                                                double* result_p) {
  if (c == NULL || result_p == NULL) {
    return -1;
  }

  double result = 0.0;
  double module_sq = 0.0;
  for (int j = 0; j < dim; j++) {
    complex_modulus_square(c + j, &module_sq);
    result += module_sq;
  }
  *result_p = result;
  return 0;
}

int c_self_add_ab_product(const complex_t* a,
#ifdef MAT_B_IS_COMPLEX
                          const complex_t* b,
#else
                          const double* b,
#endif
                          complex_t* c) {
  complex_t prod = {.re = 0.0, .im = 0.0};
#ifdef MAT_B_IS_COMPLEX
  complex_mult(a, b, &prod);
#else
  complex_mult_ext(a, *b, &prod);
#endif
  complex_add(c, &prod, c);
  return 0;
}
