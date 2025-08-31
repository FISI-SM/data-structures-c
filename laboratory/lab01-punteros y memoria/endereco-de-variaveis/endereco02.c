#include <stdio.h>

int main() {
    
    char a = '0';
    short b = 1;
    int c = 3;
    long d = 4; 
    double e = 5.;

     // & obtiene la direccion de memoria de las variables.
     // hexadecimal | decimal | contenido
    printf("&a = %p | &a = %ld | a = %c\n", &a, &a, a);
    printf("&b = %p | &b = %ld | b = %d\n", &b, &b, b);
    printf("&c = %p | &c = %ld | c = %d\n", &c, &c, c);
    printf("&d = %p | &d = %ld | d = %d\n", &d, &d, d);
    printf("&e = %p | &d = %ld | e = %lf\n\n", &e, &e, e);

    return 0;
}
