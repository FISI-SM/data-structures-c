#ifndef COMPLEX_H
#define COMPLEX_H

typedef struct {
    double re;
    double im;
} Complex;

// Constructores
Complex c_make(double re, double im);

// Operaciones básicas
Complex c_add(Complex a, Complex b);
Complex c_sub(Complex a, Complex b);
Complex c_mul(Complex a, Complex b);

// Utilidades
int c_to_string(Complex z, char *buf, int bufsize); // devuelve chars escritos (sin contar \0)
#endif
