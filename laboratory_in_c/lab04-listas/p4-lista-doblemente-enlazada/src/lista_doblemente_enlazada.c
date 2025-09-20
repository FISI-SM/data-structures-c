#include "lista_doblemente_enlazada.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct nodo
{
    int datos;
    Nodo *ptr_nodo_siguiente;
    Nodo *ptr_nodo_anterior;
};

struct lista
{
    int tamano;
    Nodo *ptr_nodo_cabeza;
    Nodo *ptr_nodo_cola; // con el puntero cola/final es un deque.
};

Lista *crear_lista()
{

    Lista *ptr_lista = (Lista *)malloc(sizeof(Lista));
    ptr_lista->tamano = 0;
    ptr_lista->ptr_nodo_cabeza = NULL;
    ptr_lista->ptr_nodo_cola = NULL;

    return ptr_lista;
}

void destruir_lista(Lista **ptr_ptr_lista)
{

    // implementacion utilizando la cabeza, tambien se puede hacer utilizando la cola.

    Lista *ptr_lista = (*ptr_ptr_lista);

    if (ptr_lista != NULL)
    { // lista no esta vacía

        Nodo *ptr_nodo_actual = ptr_lista->ptr_nodo_cabeza;

        Nodo *ptr_nodo_auxiliar;
        while (ptr_nodo_actual != ptr_lista->ptr_nodo_cola)
        {

            ptr_nodo_auxiliar = ptr_nodo_actual;
            ptr_nodo_actual = ptr_nodo_actual->ptr_nodo_siguiente;

            free(ptr_nodo_auxiliar);
        }
        free(ptr_nodo_actual);

        free(ptr_lista);
        *ptr_ptr_lista = NULL;
    }
}

int tamano_lista(Lista *ptr_lista)
{

    // TODO: Implementa esta función.

    return 0;
}

void imprimir_cabeza_lista(Lista *ptr_lista)
{

    Nodo *ptr_nodo_actual = ptr_lista->ptr_nodo_cabeza;
    printf("Lista Cabeza -> ");
    while (ptr_nodo_actual != NULL)
    {
        printf("%d -> ", ptr_nodo_actual->datos);
        ptr_nodo_actual = ptr_nodo_actual->ptr_nodo_siguiente;
    }
    printf(" NULL \n");
}

void imprimir_cola_lista(Lista *ptr_lista)
{

    Nodo *ptr_nodo_actual = ptr_lista->ptr_nodo_cola;
    printf("Lista Cola -> ");
    while (ptr_nodo_actual != NULL)
    {
        printf("%d -> ", ptr_nodo_actual->datos);
        ptr_nodo_actual = ptr_nodo_actual->ptr_nodo_anterior;
    }
    printf(" NULL \n");
}

void agregar_cabeza_lista(Lista *ptr_lista, int valor)
{

    Nodo *ptr_nodo_nuevo = (Nodo *)malloc(sizeof(Nodo));

    if (ptr_nodo_nuevo == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    ptr_nodo_nuevo->datos = valor;
    ptr_nodo_nuevo->ptr_nodo_anterior = NULL;
    ptr_nodo_nuevo->ptr_nodo_siguiente = NULL;

    if (ptr_lista->ptr_nodo_cabeza == NULL)
    {

        ptr_lista->ptr_nodo_cabeza = ptr_nodo_nuevo;

        ptr_lista->ptr_nodo_cola = ptr_nodo_nuevo;
    }
    else
    {
        ptr_nodo_nuevo->ptr_nodo_siguiente = ptr_lista->ptr_nodo_cabeza;

        ptr_lista->ptr_nodo_cabeza->ptr_nodo_anterior = ptr_nodo_nuevo;

        ptr_lista->ptr_nodo_cabeza = ptr_nodo_nuevo;
    }
    ptr_lista->tamano = ptr_lista->tamano + 1;
}

void agregar_cola_lista(Lista *ptr_lista, int valor)
{

    // TODO: Implementa esta funcion.
}

void agregar_posicion_lista(Lista *ptr_lista, int posicion)
{

    // TODO: Implementa esta funcion.
}

bool eliminar_inicio_lista(Lista *ptr_lista)
{

    // TODO: Implementa esta funcion.
    return true;
}

bool eliminar_fin_lista(Lista *ptr_lista)
{

    // TODO: Implementa esta funcion.
    return true;
}
bool eliminar_valor_lista(Lista *ptr_lista, int valor)
{

    // TODO: Implementa esta funcion.
    return true;
}

int buscar_valor_lista(Lista *ptr_lista, int valor)
{

    // TODO: Implementa esta funcion.
    return -1;
}

int buscar_posicion_lista(Lista *ptr_lista, int posicion)
{

    // TODO: Implementa esta funcion.
    return -1;
}
