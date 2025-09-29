#include "pila_como_lista_enlazada.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct nodo {
    int datos;
    Nodo *siguiente;
};

Nodo *crear_pila() {
   return NULL;
}

void destruir_pila(Nodo **ptr_nodo) {

    Nodo *ptr_nodo_aux;
    while (*ptr_nodo != NULL) {
       ptr_nodo_aux = *ptr_nodo;
       *ptr_nodo = (*ptr_nodo)->siguiente;
       free(ptr_nodo_aux);
    }
}

void imprimir_pila(Nodo *ptr_nodo) {

    //printf("Lista inicio \n");
    while (ptr_nodo != NULL) {
       printf("%d -> ", ptr_nodo->datos);
       //printf("actual: %p valor: %d siguiente: %p \n", ptr_nodo, ptr_nodo->datos, ptr_nodo->siguiente);

       ptr_nodo = ptr_nodo->siguiente;
    }
    printf("NULL \n\n");
    //printf("fin \n\n");
}

int tamano_pila(const Nodo *ptr_nodo) {

    //TODO
    return 0;
}

void apilar_pila(Nodo **ptr_ptr_nodo, int valor) {  // &l

    Nodo *ptr_nodo_nuevo = (Nodo*) malloc(sizeof(Nodo));

    if (ptr_nodo_nuevo == NULL) {
       perror("malloc");
       exit(EXIT_FAILURE);
    }

    ptr_nodo_nuevo->datos = valor;
    ptr_nodo_nuevo->siguiente = *ptr_ptr_nodo;

    *ptr_ptr_nodo = ptr_nodo_nuevo;
}

bool desapilar_pila(Nodo **ptr_ptr_nodo) {

    //TODO
    return true;
}

int buscar_valor_pila(Nodo *ptr_ptr_nodo, int valor) {  // puede retornar la posicion, si el dato fuera un tipo compuesto retornariamos el

    //TODO
    return -1;
}
