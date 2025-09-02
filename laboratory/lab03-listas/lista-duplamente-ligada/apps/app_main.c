#include "lista_doblemente_enlazada.h"
#include <stdio.h>
#include <stdlib.h> 

int main() { 
    
   printf("\n--- Lista Doblemente Enlazada ---\n\n");

   Lista *ptr_lista = crear_lista();

   imprimir_cabeza_lista(ptr_lista);

   agregar_cabeza_lista(ptr_lista, 10);
   agregar_cabeza_lista(ptr_lista, 33);
   agregar_cabeza_lista(ptr_lista, 99);
   
   imprimir_cabeza_lista(ptr_lista);

   imprimir_cola_lista(ptr_lista);

   //printf("%d \n", tamano_lista(ptr_lista));

   destruir_lista(&ptr_lista); 
   
   return 0;

}
