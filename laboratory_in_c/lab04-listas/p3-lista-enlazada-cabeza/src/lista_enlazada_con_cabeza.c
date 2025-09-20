#include "lista_enlazada_con_cabeza.h" 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>  

struct nodo {
    int datos; 
    Nodo *ptr_nodo_siguiente;  
};

struct lista {
    int tamano; 
    Nodo *ptr_nodo_cabeza;  
};

Lista *crear_lista() {

   Lista *lista = (Lista*) malloc(sizeof(Lista));
   lista->tamano = 0;
   lista->ptr_nodo_cabeza = NULL;
      
   return lista;
}

void destruir_lista(Lista **ptr_ptr_lista) {
 
    Nodo *ptr_nodo_actual = (*ptr_ptr_lista)->ptr_nodo_cabeza;
    Nodo *ptr_nodo_auxiliar;    
    while (ptr_nodo_actual != NULL) {
       ptr_nodo_auxiliar = ptr_nodo_actual;
       ptr_nodo_actual = ptr_nodo_actual->ptr_nodo_siguiente;
       free(ptr_nodo_auxiliar);          
    }
    free(*ptr_ptr_lista);
    *ptr_ptr_lista = NULL;
    
}

int tamano_lista(Lista *ptr_lista) {

    //TODO: Implementa esta funcion.
    return -1;

}

void imprimir_lista(Lista *ptr_lista) { 

    printf("Lista Cabeza { ");
    
    for (Nodo *ptr_nodo_actual = ptr_lista->ptr_nodo_cabeza; 
         ptr_nodo_actual != NULL; 
         ptr_nodo_actual = ptr_nodo_actual->ptr_nodo_siguiente) {

       printf("%d -> ", ptr_nodo_actual->datos);

    }
    printf("NULL }\n\n");

}

void agregar_inicio_lista(Lista *ptr_lista, int valor) {

    Nodo *ptr_nodo_nuevo = (Nodo*) malloc(sizeof(Nodo));
    
    if (ptr_nodo_nuevo == NULL) {
       perror("malloc");
       exit(EXIT_FAILURE);
    }

    ptr_nodo_nuevo->datos = valor;
    ptr_nodo_nuevo->ptr_nodo_siguiente = ptr_lista->ptr_nodo_cabeza;
    ptr_lista->ptr_nodo_cabeza = ptr_nodo_nuevo;   

    ptr_lista->tamano = ptr_lista->tamano + 1; 
    
} 

void agregar_final_lista(Lista *ptr_lista, int valor) {

    //TODO: Implementa esta funcion.

}

bool eliminar_inicio_lista(Lista *ptr_lista) {

    //TODO: Implementa esta funcion.

    return true;

} 

bool eliminar_final_lista(Lista *ptr_lista) {

    
    //TODO: Implementa esta funcion.
    return true;

}

bool eliminar_valor_lista(Lista *ptr_lista, int valor) {

    //TODO: Implementa esta funcion.
    return true;

}

int buscar_valor_lista(Lista *ptr_lista, int valor) {

    //TODO: Implementa esta funcion.
    return -1;

}

int buscar_posicion_lista(Lista *ptr_lista, int posicion) {

    //TODO: Implementa esta funcion.
    return -1;

}
