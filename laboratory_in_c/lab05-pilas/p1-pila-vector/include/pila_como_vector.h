#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h> 

typedef struct pila Pila;

Pila* crear_pila(int tamano);
void destruir_pila(Pila **pila);

void apilar_pila(Pila *pila, int valor);

void desapilar_pila(Pila *pila);

int tamano_pila(const Pila *pila);
int cantidad_pila(const Pila *pila);

void imprimir_pila(const Pila *pila);
