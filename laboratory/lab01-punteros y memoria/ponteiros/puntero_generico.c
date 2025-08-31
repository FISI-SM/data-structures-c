#include <stdio.h>
#include <stdlib.h>

/*
Un puntero generico es un puntero que puede apuntar a cualquier tipo de dato.

Para acceder al contenido de un puntero generico es necesario convertirlo 
primero al tipo de puntero con el que se desea trabajar.

*/

int main() {
    
    int a = 20;
    void *p = &a;

    printf("&a  = %p | a  = %d\n", &a, a);
    printf("&p  = %p | p  = %p\n\n", &p, p);

    //convierte el puntero generico a puntero de int.
    int b = *(int*)p;

    printf("&b  = %p | b  = %d\n", &b, b);

    return 0;
}
