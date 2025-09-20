#include "lista_enlazada_circular.h"
#include <stdio.h>
#include <stdlib.h>

struct nodo {
    int dato;
    struct nodo *siguiente;
};

// --- Helpers internos ---
static inline int es_vacia(const Nodo *head) { return head == NULL; }
static inline int es_unica(const Nodo *head) { return head && head->siguiente == head; }

static Nodo* obtener_ultimo(Nodo *head) {
    if (!head) return NULL;
    Nodo *cur = head;
    while (cur->siguiente != head) cur = cur->siguiente;
    return cur;
}

// --- API ---
Nodo* crear_lista(void) {
    return NULL; // lista circular vacía
}

void destruir_lista_enlazada(Nodo **ptr_ptr_head) {
    if (!ptr_ptr_head || !*ptr_ptr_head) return;
    Nodo *head = *ptr_ptr_head;
    // Romper circularidad para liberar en modo lineal
    Nodo *ult = obtener_ultimo(head);
    if (ult) ult->siguiente = NULL;

    while (head) {
        Nodo *sig = head->siguiente;
        free(head);
        head = sig;
    }
    *ptr_ptr_head = NULL;
}

int tamano_lista(const Nodo *head) {
    if (!head) return 0;
    int c = 0;
    const Nodo *cur = head;
    do {
        ++c;
        cur = cur->siguiente;
    } while (cur != head);
    return c;
}

void imprimir_lista(const Nodo *head) {
    if (!head) { printf("NULL (circular)\n"); return; }
    const Nodo *cur = head;
    do {
        printf("%d -> ", cur->dato);
        cur = cur->siguiente;
    } while (cur != head);
    printf("(vuelve a %d)\n", head->dato);
}

void agregar_inicio_lista(Nodo **ptr_ptr_head, int valor) {
    if (!ptr_ptr_head) return;
    Nodo *head = *ptr_ptr_head;
    Nodo *nuevo = (Nodo*)malloc(sizeof(Nodo));
    if (!nuevo) { perror("malloc"); exit(EXIT_FAILURE); }
    nuevo->dato = valor;

    if (!head) {
        nuevo->siguiente = nuevo;
        *ptr_ptr_head = nuevo;
        return;
    }
    Nodo *ult = obtener_ultimo(head);
    nuevo->siguiente = head;
    ult->siguiente = nuevo;
    *ptr_ptr_head = nuevo;
}

void agregar_final_lista(Nodo **ptr_ptr_head, int valor) {
    if (!ptr_ptr_head) return;
    Nodo *head = *ptr_ptr_head;
    Nodo *nuevo = (Nodo*)malloc(sizeof(Nodo));
    if (!nuevo) { perror("malloc"); exit(EXIT_FAILURE); }
    nuevo->dato = valor;

    if (!head) {
        nuevo->siguiente = nuevo;
        *ptr_ptr_head = nuevo;
        return;
    }
    Nodo *ult = obtener_ultimo(head);
    nuevo->siguiente = head;
    ult->siguiente = nuevo;
    // head no cambia
}

void agregar_ordenado_lista(Nodo **ptr_ptr_head, int valor) {
    if (!ptr_ptr_head) return;
    Nodo *head = *ptr_ptr_head;
    Nodo *nuevo = (Nodo*)malloc(sizeof(Nodo));
    if (!nuevo) { perror("malloc"); exit(EXIT_FAILURE); }
    nuevo->dato = valor;

    if (!head) {
        nuevo->siguiente = nuevo;
        *ptr_ptr_head = nuevo;
        return;
    }

    // Si va antes del head (menor o igual), es nueva cabeza
    if (valor <= head->dato) {
        Nodo *ult = obtener_ultimo(head);
        nuevo->siguiente = head;
        ult->siguiente = nuevo;
        *ptr_ptr_head = nuevo;
        return;
    }

    // Buscar posición entre head y el último antes de volver a head
    Nodo *cur = head;
    while (cur->siguiente != head && cur->siguiente->dato < valor) {
        cur = cur->siguiente;
    }
    nuevo->siguiente = cur->siguiente;
    cur->siguiente = nuevo;
}

bool eliminar_inicio_lista(Nodo **ptr_ptr_head) {
    if (!ptr_ptr_head || !*ptr_ptr_head) return false;
    Nodo *head = *ptr_ptr_head;

    if (es_unica(head)) {
        free(head);
        *ptr_ptr_head = NULL;
        return true;
    }
    Nodo *ult = obtener_ultimo(head);
    Nodo *nuevo_head = head->siguiente;
    ult->siguiente = nuevo_head;
    free(head);
    *ptr_ptr_head = nuevo_head;
    return true;
}

bool eliminar_final_lista(Nodo **ptr_ptr_head) {
    if (!ptr_ptr_head || !*ptr_ptr_head) return false;
    Nodo *head = *ptr_ptr_head;

    if (es_unica(head)) {
        free(head);
        *ptr_ptr_head = NULL;
        return true;
    }
    // ubicar penúltimo
    Nodo *prev = head;
    while (prev->siguiente->siguiente != head) prev = prev->siguiente;
    Nodo *ult = prev->siguiente;
    prev->siguiente = head;
    free(ult);
    return true;
}

bool eliminar_valor_lista(Nodo **ptr_ptr_head, int valor) {
    if (!ptr_ptr_head || !*ptr_ptr_head) return false;
    Nodo *head = *ptr_ptr_head;

    // Caso único
    if (es_unica(head)) {
        if (head->dato == valor) {
            free(head);
            *ptr_ptr_head = NULL;
            return true;
        }
        return false;
    }

    // Si el head es el valor a eliminar
    if (head->dato == valor) {
        return eliminar_inicio_lista(ptr_ptr_head);
    }

    // Buscar en el resto
    Nodo *prev = head;
    Nodo *cur = head->siguiente;
    while (cur != head && cur->dato != valor) {
        prev = cur;
        cur = cur->siguiente;
    }
    if (cur == head) return false; // no encontrado
    prev->siguiente = cur->siguiente;
    free(cur);
    return true;
}

int buscar_valor_lista(Nodo *head, int valor) {
    if (!head) return -1;
    int idx = 0;
    Nodo *cur = head;
    do {
        if (cur->dato == valor) return idx;
        cur = cur->siguiente;
        ++idx;
    } while (cur != head);
    return -1;
}

int buscar_posicion_lista(Nodo *head, int pos) {
    if (!head || pos < 0) return -1;
    int idx = 0;
    Nodo *cur = head;
    do {
        if (idx == pos) return cur->dato;
        cur = cur->siguiente;
        ++idx;
    } while (cur != head);
    return -1;
}
