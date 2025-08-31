#include <stdio.h>

/*
Punteros

Un puntero (apuntador) es un tipo especial de variable capaz de almacenar una direccion de memoria. 
Solo podra almacenar la direccion de memoria de su respectivo tipo de dato.

Para declarar una variable puntero usamos el operador *. 

Las variables del tipo puntero ocupan 8 bytes, independientemente del tipo. 

*/


int main() {
    int *p = NULL;
    
    if (p == NULL) {
        printf("Buena practica es inicializar los punteros.\n\n");

    } 
    printf("&p = %p || p = %p \n\n", &p, p);
    
    // el puntero recibiendo una direccion cualquiera de memoria.
    p = 0x7ffd5e9698c1; 
    printf("&p = %p || p = %p \n", &p, p);
   
    
 /*   int *p1 = 0xF;
    //decimal
    printf("&p1 = %p || p = %ld \n", &p1, p1);

    // binario 
    printf("&p1 = %p || p = %lb \n", &p1, p1);

    // hexadecimal 
    printf("&p1 = %p || p = %p \n", &p1, p1);

   */  

    return 0;
}
