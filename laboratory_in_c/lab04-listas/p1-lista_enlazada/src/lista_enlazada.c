#include "lista_enlazada.h"

#include <stdio.h>

#include <stdlib.h>

struct nodo {
    int dato;
    struct nodo * proximo;
};

// --- Creación / destrucción ---
Nodo * crear_lista(void) {
    return NULL;
}

static void destruir_recursivo(Nodo * n) {
    if (n) {
        destruir_recursivo(n -> proximo);
        free(n);
    }
}

void destruir_lista(Nodo ** ptr_ptr_nodo) {
    if (!ptr_ptr_nodo) return;
    destruir_recursivo( * ptr_ptr_nodo);
    * ptr_ptr_nodo = NULL;
}

// --- Métricas / impresión ---
int tamano_lista(const Nodo * ptr_nodo) {
    int c = 0;
    while (ptr_nodo) {
        ++c;
        ptr_nodo = ptr_nodo -> proximo;
    }
    return c;
}

void imprimir_lista(const Nodo * ptr_nodo) {
    while (ptr_nodo) {
        printf("%d -> ", ptr_nodo -> dato);
        ptr_nodo = ptr_nodo -> proximo;
    }
    printf("NULL\n");
}

// --- Inserciones ---
void agregar_inicio_lista(Nodo ** ptr_ptr_nodo, int valor) {
    Nodo * nuevo = (Nodo * ) malloc(sizeof(Nodo));
    if (!nuevo) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    nuevo -> dato = valor;
    nuevo -> proximo = * ptr_ptr_nodo;* ptr_ptr_nodo = nuevo;
}

void agregar_final_lista(Nodo ** ptr_ptr_nodo, int valor) {
    Nodo * nuevo = (Nodo * ) malloc(sizeof(Nodo));
    if (!nuevo) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    nuevo -> dato = valor;
    nuevo -> proximo = NULL;
    if (! * ptr_ptr_nodo) {
        * ptr_ptr_nodo = nuevo;
        return;
    }
    Nodo * cur = * ptr_ptr_nodo;
    while (cur -> proximo) cur = cur -> proximo;
    cur -> proximo = nuevo;
}

void agregar_ordenado_lista(Nodo ** ptr_ptr_nodo, int valor) {
    Nodo * nuevo = (Nodo * ) malloc(sizeof(Nodo));
    if (!nuevo) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    nuevo -> dato = valor;
    nuevo -> proximo = NULL;
    Nodo * cur = * ptr_ptr_nodo, * prev = NULL;
    while (cur && cur -> dato < valor) {
        prev = cur;
        cur = cur -> proximo;
    }
    if (!prev) {
        nuevo -> proximo = * ptr_ptr_nodo;* ptr_ptr_nodo = nuevo;
    } else {
        nuevo -> proximo = cur;
        prev -> proximo = nuevo;
    }
}

// --- Eliminaciones ---
bool eliminar_inicio_lista(Nodo ** ptr_ptr_nodo) {
    if (!ptr_ptr_nodo || ! * ptr_ptr_nodo) return false;
    Nodo * prim = * ptr_ptr_nodo;* ptr_ptr_nodo = prim -> proximo;
    free(prim);
    return true;
}

bool eliminar_final_lista(Nodo ** ptr_ptr_nodo) {
    if (!ptr_ptr_nodo || ! * ptr_ptr_nodo) return false;
    Nodo * cur = * ptr_ptr_nodo, * prev = NULL;
    while (cur -> proximo) {
        prev = cur;
        cur = cur -> proximo;
    }
    if (!prev) {
        free(cur);* ptr_ptr_nodo = NULL;
    } else {
        prev -> proximo = NULL;
        free(cur);
    }
    return true;
}

bool eliminar_valor_lista(Nodo ** ptr_ptr_nodo, int valor) {
    if (!ptr_ptr_nodo || ! * ptr_ptr_nodo) return false;
    Nodo * cur = * ptr_ptr_nodo, * prev = NULL;
    while (cur && cur -> dato != valor) {
        prev = cur;
        cur = cur -> proximo;
    }
    if (!cur) return false;
    if (!prev) * ptr_ptr_nodo = cur -> proximo;
    else prev -> proximo = cur -> proximo;
    free(cur);
    return true;
}

// --- Búsquedas ---
int buscar_valor_lista(Nodo * ptr_nodo, int valor) {
    int idx = 0;
    while (ptr_nodo) {
        if (ptr_nodo -> dato == valor) return idx;
        ptr_nodo = ptr_nodo -> proximo;
        ++idx;
    }
    return -1;
}

int buscar_posicion_lista(Nodo * ptr_nodo, int pos) {
    if (pos < 0) return -1;
    int idx = 0;
    while (ptr_nodo && idx < pos) {
        ptr_nodo = ptr_nodo -> proximo;
        ++idx;
    }
    return ptr_nodo ? ptr_nodo -> dato : -1;
}

// --- Utilidad ---
void juntar_lista(Nodo ** ptr_ptr_lista01, Nodo ** ptr_ptr_lista02) {
    if (!ptr_ptr_lista01 || !ptr_ptr_lista02) return;
    if (! * ptr_ptr_lista01) {
        * ptr_ptr_lista01 = * ptr_ptr_lista02;* ptr_ptr_lista02 = NULL;
        return;
    }
    if (! * ptr_ptr_lista02) return;
    Nodo * cur = * ptr_ptr_lista01;
    while (cur -> proximo) cur = cur -> proximo;
    cur -> proximo = * ptr_ptr_lista02;* ptr_ptr_lista02 = NULL;
}