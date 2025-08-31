#include <stdio.h>

int main() {
    
    int a;

    // tamaño de variables
    printf("sizeof(a)      = %ld bytes\n", sizeof(a));
    
    unsigned long tamano_a = sizeof(a);
    printf("tamano_a      = %ld bytes\n\n", tamano_a);

    // tamaño de los tipos de datos
    printf("sizeof(char)   = %ld bytes\n", sizeof(char));
    printf("sizeof(int)    = %ld bytes\n", sizeof(int));

    printf("sizeof(short)  = %ld bytes\n", sizeof(short));
    printf("sizeof(float)  = %ld bytes\n", sizeof(float));
    printf("sizeof(double) = %ld bytes\n", sizeof(double));
    printf("sizeof(long)   = %ld bytes\n", sizeof(long));
    printf("sizeof(unsigned long) = %ld bytes\n\n", sizeof(unsigned long));
  
    // tamaño de punteros. 
    // los punteros guardan direcciones de memoria y las direcciones son siempre del mismo tamaño.
    printf("sizeof(void *)  = %ld bytes\n", sizeof(void *));
    printf("sizeof(char *)  = %ld bytes\n", sizeof(char *));
    printf("sizeof(int *)   = %ld bytes\n", sizeof(int *));
    printf("sizeof(int **)  = %ld bytes\n", sizeof(int **));
    printf("sizeof(int ***) = %ld bytes\n", sizeof(int ***));
    printf("sizeof(float *) = %ld bytes\n", sizeof(float *));

    return 0;
}
