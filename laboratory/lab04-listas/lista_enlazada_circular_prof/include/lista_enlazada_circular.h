#ifndef LISTA_ENLAZADA_CIRCULAR_H
#define LISTA_ENLAZADA_CIRCULAR_H

#include <stdbool.h>

typedef struct nodo Nodo;

// Creación / destrucción
Nodo* crear_lista(void);
void  destruir_lista_enlazada(Nodo **ptr_ptr_nodo);

// Métricas y visualización
int   tamano_lista(const Nodo *ptr_nodo);
void  imprimir_lista(const Nodo *ptr_nodo);

// Inserciones
void  agregar_inicio_lista(Nodo **ptr_ptr_nodo, int valor);
void  agregar_final_lista(Nodo **ptr_ptr_nodo, int valor);
void  agregar_ordenado_lista(Nodo **ptr_ptr_nodo, int valor); // ascendente

// Eliminaciones
bool  eliminar_inicio_lista(Nodo **ptr_ptr_nodo);
bool  eliminar_final_lista(Nodo **ptr_ptr_nodo);
bool  eliminar_valor_lista(Nodo **ptr_ptr_nodo, int valor);   // elimina primera ocurrencia

// Búsquedas (0-based)
int   buscar_valor_lista(Nodo *ptr_nodo, int valor);   // índice o -1
int   buscar_posicion_lista(Nodo *ptr_nodo, int pos);  // valor o -1 si fuera de rango

#endif // LISTA_ENLAZADA_CIRCULAR_H
