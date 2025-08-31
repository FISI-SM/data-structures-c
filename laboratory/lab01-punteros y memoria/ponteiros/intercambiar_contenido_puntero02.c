#include <stdio.h>

int main() {
    
    int a = 20;
    int *p = &a;
    int q;
    
    printf("Direccion de Memoria | Contenido \n");

    printf("&a = %p | a = %d\n", &a, a);
    printf("&p = %p | p = %p\n", &p, p);
    printf("&p = %p | *p = %d\n\n", &p, *p);
  
    // Obtiene el contenido de la variable cuya direccion guarda ( p ). 
    q = *p;
    printf("&q = %p | q = %d\n\n", &q, q);

    // Modifica el contenido de la variable cuya direccion guarda ( p ), en este caso la variable ( a ); 
    *p = 50;
    printf("&a = %p | a = %d\n", &a, a);
    printf("&p = %p | p = %p\n\n", &p, p);
    
    // Modifica el contenido de la variable ( p ).  
    p = &q;
     
    printf("&p = %p | p = %p\n", &p, p);
    printf("&q = %p | q = %d\n\n", &q, q);
    
    return 0;
}
