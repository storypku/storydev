#ifndef MPI_MATRIX_MULT_MATRIX_HELPER_H_
#define MPI_MATRIX_MULT_MATRIX_HELPER_H_

#define IN
#define OUT
#define INOUT

#include "complex.h"

// N denotes the dimension of square matrices. N x N
#define N 100

void set_elements_of_row_for_mat_a(int i, int dim, OUT complex_t *a);
void set_elements_of_col_for_mat_b(int j, int dim,
#ifdef MAT_B_IS_COMPLEX
                                   OUT complex_t *b
#else
                                   OUT double *b
#endif
);
int calc_sum_of_modulus_square_of_row_for_mat_c(const complex_t *c, int dim,
                                                double *result);

// c += a * b where a, b, c are all complex numbers
int c_self_add_ab_product(const complex_t *a,
#ifdef MAT_B_IS_COMPLEX
                          const complex_t *b,
#else
                          const double *b,
#endif
                          INOUT complex_t *c);

#endif  // MPI_MATRIX_MULT_MATRIX_HELPER_H_
