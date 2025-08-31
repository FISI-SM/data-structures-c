#include <stdio.h>
#include <stdlib.h>


int main() {
    
    int a[3] = {10, 20, 30}; 
    int *p = &a;  
    
    printf("&a    = %p | a = %d\n", &a, a[0]);
    printf("&a[0] = %p | a = %d\n", &a[0], a[0]);
    printf("&a[1] = %p | b = %d\n", &a[1], a[1]);
    printf("&b[2] = %p | c = %d\n", &a[2], a[2]);
    printf("\n");

    //direccion de memoria de la variable a

    //posicion inicial del vector
    printf("&p = %p | p = %p | p = %ld | *p = %d \n\a", &p, p, p, *p);
    
    // avanza 8 bytes porque es un puntero a int
    p = p + 2; 
    printf("&p = %p | p = %p | p = %ld | *p = %d \n", &p, p, p, *p);

    // retrocede 4 bytes porque es un puntero a int
    p--;  
    // %ld formatea en decimal 
    printf("&p = %p | p = %p | p = %ld | *p = %d \n", &p, p, p, *p);

    // avanza 4 bytes porque es un puntero a int
    p++; 
    printf("&p = %p | p = %p | p = %ld | *p = %d \n", &p, p, p, *p);

    return 0;
}
