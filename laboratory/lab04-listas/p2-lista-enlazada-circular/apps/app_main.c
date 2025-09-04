#include "lista_enlazada_circular.h"
#include <stdio.h>
#include <stdlib.h> 


int main() { 
    
   printf("\n--- Lista Enlazada Circular---\n\n");

   Nodo *lista = crear_lista();

   imprimir_lista(lista);

   agregar_inicio_lista(&lista, 10);

   imprimir_lista(lista);

   agregar_inicio_lista(&lista, 33);
   imprimir_lista(lista);

   agregar_inicio_lista(&lista, 99);
   imprimir_lista(lista);

   agregar_final_lista(&lista, 17);
   imprimir_lista(lista);

  // eliminar_valor_lista(&lista, 99);
  // imprimir_lista(lista);
   
  agregar_final_lista(&lista, 44);
  imprimir_lista(lista); 

  eliminar_final_lista(&lista);
  imprimir_lista(lista);

  destruir_lista_enlazada(&lista);
   
   return 0;

}
