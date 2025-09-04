#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h> 


typedef struct nodo Nodo;

typedef struct lista Lista;

Lista *crear_lista();
void destruir_lista(Lista **ptr_ptr_lista);

int tamano_lista(Lista *ptr_lista);

void imprimir_lista(Lista *ptr_lista);

void agregar_inicio_lista(Lista *ptr_lista, int valor);
void agregar_final_lista(Lista *ptr_lista, int valor);

bool eliminar_inicio_lista(Lista *ptr_lista); 
bool eliminar_final_lista(Lista *ptr_lista); 
bool eliminar_valor_lista(Lista *ptr_lista, int valor); 

int buscar_valor_lista(Lista *ptr_lista, int valor);
int buscar_posicion_lista(Lista *ptr_lista, int posicion);
