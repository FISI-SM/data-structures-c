#include "pila_como_vector.h"
#include <stdio.h>
#include <stdlib.h> 

int main() { 
    
   printf("\n--- PILA -  ---\n\n");
    
   Pila *pila = crear_pila(4);

   imprimir_pila(pila);
   printf("tamaño: %d\n", tamaño_pila(pila));
   printf("cantidad: %d \n\n", cantidad_pila(pila));

   apilar_pila(pila, 13);
   apilar_pila(pila, 9);  
  
   imprimir_pila(pila);
   printf("tamaño: %d\n", tamaño_pila(pila));
   printf("cantidad: %d \n\n", cantidad_pila(pila));

   apilar_pila(pila, 4);
   apilar_pila(pila, 2);  

   imprimir_pila(pila);
   printf("tamaño: %d\n", tamaño_pila(pila));
   printf("cantidad: %d \n\n", cantidad_pila(pila));

   apilar_pila(pila, 1);
   apilar_pila(pila, 10);
   apilar_pila(pila, 44);
   apilar_pila(pila, 33);
      
   imprimir_pila(pila);
   printf("tamaño: %d\n", tamaño_pila(pila));
   printf("cantidad: %d \n\n", cantidad_pila(pila));

   desapilar_pila(pila);
   desapilar_pila(pila);

   imprimir_pila(pila);
   printf("tamaño: %d\n", tamaño_pila(pila));
   printf("cantidad: %d \n\n", cantidad_pila(pila));

   desapilar_pila(pila);
   desapilar_pila(pila);

   imprimir_pila(pila);
   printf("tamaño: %d\n", tamaño_pila(pila));
   printf("cantidad: %d \n\n", cantidad_pila(pila));

   desapilar_pila(pila);
   desapilar_pila(pila);
   desapilar_pila(pila);

   imprimir_pila(pila);
   printf("tamaño: %d\n", tamaño_pila(pila));
   printf("cantidad: %d \n\n", cantidad_pila(pila));
 
   destruir_pila(&pila);
   
   return 0;
}
