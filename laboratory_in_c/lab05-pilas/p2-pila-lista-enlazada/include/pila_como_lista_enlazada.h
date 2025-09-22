#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h> 

typedef struct nodo Nodo;

Nodo* crear_pila();
void destruir_pila(Nodo **ptr_ptr_nodo);

int tamano_pila(const Nodo *ptr_nodo);

void imprimir_pila(Nodo *ptr_nodo);

void apilar_pila(Nodo **ptr_ptr_nodo, int valor); 

bool desapilar_pila(Nodo **ptr_ptr_nodo); // 0 no removio, 1 removio

int buscar_valor_pila(Nodo *ptr_nodo, int valor);
