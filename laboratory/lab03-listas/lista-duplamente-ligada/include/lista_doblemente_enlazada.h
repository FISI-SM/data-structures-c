#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h> 

typedef struct no Nodo;

typedef struct lista Lista;

Lista *crear_lista();
void destruir_lista(Lista **ptr_ptr_lista);

int tamano_lista(Lista *ptr_lista);

void imprimir_cabeza_lista(Lista *ptr_lista);
void imprimir_cola_lista(Lista *ptr_lista);

void agregar_cabeza_lista(Lista *ptr_lista, int valor);
void agregar_cola_lista(Lista *ptr_lista, int valor);
void agregar_posicion_lista(Lista *ptr_lista, int posicion);

bool remover_inicio_lista(Lista *ptr_lista); 
bool remover_fin_lista(Lista *ptr_lista); 
bool remover_valor_lista(Lista *ptr_lista, int valor); 

int buscar_valor_lista(Lista *ptr_lista, int valor);
int buscar_posicion_lista(Lista *ptr_lista, int posicion);
