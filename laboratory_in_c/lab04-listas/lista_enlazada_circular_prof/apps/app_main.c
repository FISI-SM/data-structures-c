#include "lista_enlazada_circular.h"
#include <stdio.h>

static void demo(void) {
    Nodo *lista = crear_lista();

    // Inserciones
    agregar_inicio_lista(&lista, 20);
    agregar_inicio_lista(&lista, 10);
    agregar_final_lista(&lista, 40);
    agregar_ordenado_lista(&lista, 30); // queda 10 -> 20 -> 30 -> 40 -> (vuelve a 10)
    printf("Lista: "); imprimir_lista(lista);

    // Búsquedas
    printf("tamano: %d\n", tamano_lista(lista));
    printf("buscar_valor 30 -> idx: %d\n", buscar_valor_lista(lista, 30));
    printf("buscar_posicion 2 -> %d\n", buscar_posicion_lista(lista, 2));

    // Eliminaciones
    eliminar_inicio_lista(&lista);  // quita 10
    eliminar_final_lista(&lista);   // quita 40
    printf("Luego de eliminar inicio y final: "); imprimir_lista(lista);

    eliminar_valor_lista(&lista, 30);
    printf("Eliminar 30: "); imprimir_lista(lista);

    destruir_lista_enlazada(&lista);
}

int main(void) {
    demo();
    return 0;
}
