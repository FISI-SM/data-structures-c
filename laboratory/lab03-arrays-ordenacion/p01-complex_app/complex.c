#include "complex.h"
#include <stdio.h>

static double fix_neg_zero(double x) {
    if (x == 0.0) return 0.0;
    return x;
}

Complex c_make(double re, double im) {
    Complex z; z.re = re; z.im = im; return z;
}

Complex c_add(Complex a, Complex b) {
    return c_make(a.re + b.re, a.im + b.im);
}

Complex c_sub(Complex a, Complex b) {
    return c_make(a.re - b.re, a.im - b.im);
}

Complex c_mul(Complex a, Complex b) {
    return c_make(a.re*b.re - a.im*b.im, a.re*b.im + a.im*b.re);
}

int c_to_string(Complex z, char *buf, int bufsize) {
    z.re = fix_neg_zero(z.re);
    z.im = fix_neg_zero(z.im);
    char sign = (z.im < 0) ? '-' : '+';
    double aim = (z.im < 0) ? -z.im : z.im;
    return snprintf(buf, bufsize, "%.2f %c %.2fi", z.re, sign, aim);
}
