#include "lista_enlazada.h"
#include <stdio.h>
#include <stdlib.h> 

int main() { 
    
   printf("\n--- Lista Enlazada ---\n\n");
   Nodo *lista = crear_lista();
   Nodo *lista02 = crear_lista();

   imprimir_lista(lista);

  // agregar_inicio_lista(&lista, 10);
  // imprimir_lista(lista);

  //  agregar_inicio_lista(&lista, 33);
  // imprimir_lista(lista);

   agregar_inicio_lista(&lista, 99);
  // imprimir_lista(lista);

   agregar_inicio_lista(&lista, 17);
  //  imprimir_lista(lista);

  //agregar_inicio_lista(&lista02, 1);
  //agregar_inicio_lista(&lista02, 2);
  //agregar_inicio_lista(&lista02, 3);

  imprimir_lista(lista);
  imprimir_lista(lista02);

  juntar_lista(&lista, &lista02);

  imprimir_lista(lista);
  imprimir_lista(lista02);

   eliminar_valor_lista(&lista, 99);
   imprimir_lista(lista);
   
   agregar_final_lista(&lista, 44);
   imprimir_lista(lista);

   eliminar_final_lista(&lista);
   imprimir_lista(lista);

   return 0;

}
