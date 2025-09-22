#include "pila_como_lista_enlazada.h"
#include <stdio.h>
#include <stdlib.h>

int main() {

   printf("\n--- Pila como Lista Enlazada ---\n\n");

   Nodo *pila = crear_pila();

   imprimir_pila(pila);

   apilar_pila(&pila, 10);
   imprimir_pila(pila);

   apilar_pila(&pila, 33);
   imprimir_pila(pila);

   apilar_pila(&pila, 99);
   imprimir_pila(pila);

   apilar_pila(&pila, 17);
   imprimir_pila(pila);

   apilar_pila(&pila, 44);
   imprimir_pila(pila);

   desapilar_pila(&pila); // necesita implementar
   imprimir_pila(pila);

   return 0;
}
