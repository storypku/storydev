#include "complex.h"

#include <math.h>
#include <stdlib.h>

int complex_add(const complex_t *a, const complex_t *b, complex_t *c) {
  if (a == NULL || b == NULL || c == NULL) {
    return -1;
  }
  double re = a->re + b->re;
  double im = a->im + b->im;
  c->re = re;
  c->im = im;
  return 0;
}

int complex_sub(const complex_t *a, const complex_t *b, complex_t *c) {
  if (a == NULL || b == NULL || c == NULL) {
    return -1;
  }
  double re = a->re - b->re;
  double im = a->im - b->im;
  c->re = re;
  c->im = im;
  return 0;
}

int complex_mult(const complex_t *a, const complex_t *b, complex_t *c) {
  if (a == NULL || b == NULL || c == NULL) {
    return -1;
  }
  double re = a->re * b->re - a->im * b->im;
  double im = a->re * b->im + a->im * b->re;
  c->re = re;
  c->im = im;
  return 0;
}

static int complex_div_ext_internal(complex_t *z, double factor) {
  z->re /= factor;
  z->im /= factor;
  return 0;
}

int complex_div(const complex_t *a, const complex_t *b, complex_t *c) {
  if (a == NULL || b == NULL || c == NULL) {
    return -1;
  }
  if (b->re == 0 && b->im == 0) {  // Can't divide by zero
    return -1;
  }

  double modulus_sq_of_b = 0.0;
  complex_modulus_square(b, &modulus_sq_of_b);

  complex_t b_conj;
  complex_conjugate(b, &b_conj);
  complex_mult(a, &b_conj, c);
  complex_div_ext_internal(c, modulus_sq_of_b);
  return 0;
}

int complex_conjugate(const complex_t *a, complex_t *b) {
  if (a == NULL || b == NULL) {
    return -1;
  }
  b->re = a->re;
  b->im = -a->im;
  return 0;
}

int complex_mult_ext(const complex_t *z, double factor, complex_t *result) {
  if (z == NULL || result == NULL) {
    return -1;
  }
  result->re = z->re * factor;
  result->im = z->im * factor;
  return 0;
}

int complex_div_ext(const complex_t *z, double factor, complex_t *result) {
  if (z == NULL || result == NULL) {
    return -1;
  }
  if (factor == 0) {
    return -2;
  }
  result->re = z->re / factor;
  result->im = z->im / factor;
  return 0;
}

/* z=a+bi => |z| = sqrt(a^2 + b^2) */
int complex_modulus(const complex_t *z, double *result) {
  if (z == NULL || result == NULL) {
    return -1;
  }
  *result = sqrt(z->re * z->re + z->im * z->im);
  return 0;
}

int complex_modulus_square(const complex_t *z, double *result) {
  if (z == NULL || result == NULL) {
    return -1;
  }
  *result = z->re * z->re + z->im * z->im;
  return 0;
}
