#ifndef MPI_MATRIX_MULT_COMPLEX_T_H
#define MPI_MATRIX_MULT_COMPLEX_T_H

#include <stdlib.h>

typedef struct _complex {
  double re;
  double im;
} complex_t;

inline int complex_init(double re, double im, complex_t *z) {
  if (z == NULL) {
    return -1;
  }
  z->re = re;
  z->im = im;
  return 0;
}

inline int complex_copy(const complex_t *src, complex_t *dest) {
  if (src == NULL || dest == NULL) {
    return -1;
  }
  if (dest != src) {
    dest->re = src->re;
    dest->im = src->im;
  }
  return 0;
}

// c = a + b
int complex_add(const complex_t *a, const complex_t *b, complex_t *c);
// c = a - b
int complex_sub(const complex_t *a, const complex_t *b, complex_t *c);
// c = a * b
int complex_mult(const complex_t *a, const complex_t *b, complex_t *c);
// c = a / b
int complex_div(const complex_t *a, const complex_t *b, complex_t *c);
// b = a~
int complex_conjugate(const complex_t *a, complex_t *b);

// (a+bi) * f
int complex_mult_ext(const complex_t *z, double factor, complex_t *result);
int complex_div_ext(const complex_t *z, double factor, complex_t *result);

/* z=a+bi => |z| = sqrt(a^2 + b^2) */
int complex_modulus(const complex_t *z, double *result);
/* z=a+bi => |z|^2 = a^2 + b^2 */
int complex_modulus_square(const complex_t *z, double *result);

#endif  // MPI_MATRIX_MULT_COMPLEX_T_H
