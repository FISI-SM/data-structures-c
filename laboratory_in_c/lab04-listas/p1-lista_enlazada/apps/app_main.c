#include "lista_enlazada.h"

#include <stdio.h>

static void demo_basica(void) {
    Nodo * lista = crear_lista();
    Nodo * lista2 = crear_lista();

    agregar_inicio_lista( & lista, 99);
    agregar_inicio_lista( & lista, 17);
    printf("Lista inicial: ");
    imprimir_lista(lista);

    printf("Agregar final 44: ");
    agregar_final_lista( & lista, 44);
    imprimir_lista(lista);

    printf("Eliminar valor 99: ");
    eliminar_valor_lista( & lista, 99);
    imprimir_lista(lista);

    printf("Agregar ordenado 10, 30, 20:\n");
    agregar_ordenado_lista( & lista, 10);
    agregar_ordenado_lista( & lista, 30);
    agregar_ordenado_lista( & lista, 20);
    imprimir_lista(lista);

    printf("Tamano: %d\n", tamano_lista(lista));
    printf("Buscar valor 20 -> idx: %d\n", buscar_valor_lista(lista, 20));
    printf("Valor en posicion 2: %d\n", buscar_posicion_lista(lista, 2));

    printf("\nLista2: 1->2->3\n");
    agregar_final_lista( & lista2, 1);
    agregar_final_lista( & lista2, 2);
    agregar_final_lista( & lista2, 3);
    imprimir_lista(lista2);

    printf("\nJuntar lista += lista2\n");
    juntar_lista( & lista, & lista2);
    printf("Lista: ");
    imprimir_lista(lista);
    printf("Lista2: ");
    imprimir_lista(lista2);

    printf("Eliminar final: ");
    eliminar_final_lista( & lista);
    imprimir_lista(lista);
    printf("Eliminar inicio: ");
    eliminar_inicio_lista( & lista);
    imprimir_lista(lista);

    destruir_lista( & lista);
    destruir_lista( & lista2);
}

int main(void) {
    printf("\n--- Lista Enlazada (Demo) ---\n\n");
    demo_basica();
    return 0;
}