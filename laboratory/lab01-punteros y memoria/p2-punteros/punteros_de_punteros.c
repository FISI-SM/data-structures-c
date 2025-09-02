#include <stdio.h>
#include <stdlib.h>

/* 
Un puntero a un puntero consiste en una variable que guarda la direccion de otra, 
esta otra a su vez guarda la direccion de la variable que tiene un tipo de dato comun.

Asi, un puntero puede apuntar a otro puntero, que, a su vez, 
apunta a otro puntero, que apunta a un tercer puntero y asi sucesivamente.
*/

int main() {

    int a = 20;
    int *p1 = &a;
    int* *p2 = &p1;

    printf("&a  = %p | a  = %d\n", &a, a);
    printf("&p1 = %p | p1 = %p | *p1 = %d\n", &p1, p1, *p1);
    printf("&p2 = %p | p2 = %p | *p2 = %p | **p2 = %d\n\n", &p2, p2, *p2, **p2);

    **p2 = 50;

    printf("&a  = %p | a  = %d\n", &a, a);
    printf("&p1 = %p | p1 = %p | *p1 = %d\n", &p1, p1, *p1);
    printf("&p2 = %p | p2 = %p | *p2 = %p | **p2 = %d\n\n", &p2, p2, *p2, **p2);

    return 0;
}
