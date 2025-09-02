#include "lista_enlazada_con_cabeza.h"
#include <stdio.h>
#include <stdlib.h> 

int main() { 
    
   printf("\n--- Lista Enlazada con Cabeza ---\n\n");

   Lista *lista = crear_lista();

   imprimir_lista(lista);

   agregar_inicio_lista(lista, 10);
   agregar_inicio_lista(lista, 33);
   agregar_inicio_lista(lista, 99);
   
   imprimir_lista(lista);

   printf("%d \n", tamaño_lista(lista));

   destruir_lista(&lista);
   
   return 0;

}
