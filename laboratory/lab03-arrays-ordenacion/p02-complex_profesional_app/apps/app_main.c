#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "complex.h"

static void usage(const char *prog) {
    fprintf(stderr, "Uso:\n");
    fprintf(stderr, "  %s add re1 im1 re2 im2\n", prog);
    fprintf(stderr, "  %s sub re1 im1 re2 im2\n", prog);
    fprintf(stderr, "  %s mul re1 im1 re2 im2\n", prog);
    fprintf(stderr, "\nEjemplos:\n");
    fprintf(stderr, "  %s add 1 2 3 4     # (1+2i) + (3+4i)\n", prog);
    fprintf(stderr, "  %s sub 5 0 2 -3    # (5+0i) - (2-3i)\n", prog);
    fprintf(stderr, "  %s mul -1 0 0 2    # (-1+0i) * (0+2i)\n", prog);
}

int main(int argc, char **argv) {
    if (argc != 6) {
        usage(argv[0]);
        return 1;
    }

    const char *op = argv[1];
    char *end = NULL;

    double re1 = strtod(argv[2], &end);
    if (*end != '\0') { fprintf(stderr, "Error: re1 no es número válido\n"); return 1; }

    double im1 = strtod(argv[3], &end);
    if (*end != '\0') { fprintf(stderr, "Error: im1 no es número válido\n"); return 1; }

    double re2 = strtod(argv[4], &end);
    if (*end != '\0') { fprintf(stderr, "Error: re2 no es número válido\n"); return 1; }

    double im2 = strtod(argv[5], &end);
    if (*end != '\0') { fprintf(stderr, "Error: im2 no es número válido\n"); return 1; }

    Complex a = c_make(re1, im1);
    Complex b = c_make(re2, im2);
    Complex r;

    if (strcmp(op, "add") == 0) {
        r = c_add(a, b);
    } else if (strcmp(op, "sub") == 0) {
        r = c_sub(a, b);
    } else if (strcmp(op, "mul") == 0) {
        r = c_mul(a, b);
    } else {
        fprintf(stderr, "Operación desconocida: %s\n", op);
        usage(argv[0]);
        return 1;
    }

    char bufA[64], bufB[64], bufR[64];
    c_to_string(a, bufA, sizeof(bufA));
    c_to_string(b, bufB, sizeof(bufB));
    c_to_string(r, bufR, sizeof(bufR));

    printf("A = %s\n", bufA);
    printf("B = %s\n", bufB);
    printf("Resultado (%s) = %s\n", op, bufR);

    return 0;
}
