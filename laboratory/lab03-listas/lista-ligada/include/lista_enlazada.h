#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct nodo Nodo;

Nodo* crear_lista();
void destruir_lista(Nodo **ptr_ptr_nodo);

int tamano_lista(const Nodo *ptr_nodo);

void imprimir_lista(Nodo *ptr_nodo);

void agregar_inicio_lista(Nodo **ptr_ptr_nodo, int valor);
void agregar_final_lista(Nodo **p, int valor);
void agregar_ordenado_lista(Nodo **ptr_ptr_nodo, int valor);

bool eliminar_inicio_lista(Nodo **ptr_ptr_nodo); // 0 no elimino y 1 elimino
bool eliminar_final_lista(Nodo **ptr_ptr_nodo);
bool eliminar_valor_lista(Nodo **ptr_ptr_nodo, int valor);

int buscar_valor_lista(Nodo *ptr_nodo, int valor);
int buscar_posicion_lista(Nodo *ptr_nodo, int posicion);

void juntar_lista(Nodo **ptr_ptr_lista01, Nodo **ptr_ptr_lista02);
