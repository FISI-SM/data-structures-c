#include <stdio.h>
#include <stdbool.h>
#include "vector_dinamico.h"

static void limpiar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}
static int pedir_int(const char * msg) {
    int x;
    while (1) {
        printf("%s", msg);
        if (scanf("%d", & x) == 1) {
            limpiar_buffer();
            return x;
        }
        printf("Entrada invalida.\n");
        limpiar_buffer();
    }
}
static bool pedir_bool_si_no(const char * msg) {
    char c;
    while (1) {
        printf("%s [s/n]: ", msg);
        c = (char) getchar();
        limpiar_buffer();
        if (c == 's' || c == 'S') return true;
        if (c == 'n' || c == 'N') return false;
    }
}
static void menu(void) {
    printf("\n---------------------------------------\n");
    printf("       TAD: VECTOR DINAMICO (VD)       \n");
    printf("---------------------------------------\n");
    printf("1) Anadir valor\n");
    printf("2) Eliminar en indice\n");
    printf("3) Buscar valor\n");
    printf("4) Imprimir\n");
    printf("5) Tamano (capacidad)\n");
    printf("6) Cantidad de elementos\n");
    printf("7) Acceder (sin verificacion)\n");
    printf("8) Acceder (verificado)\n");
    printf("9) Salir\n");
    printf("---------------------------------------\n");
}

int main(void) {
    int cap = pedir_int("Capacidad inicial (ej. 4): ");
    bool ord = pedir_bool_si_no("¿Mantener orden ascendente?");

    VD * vd = crear_vd(cap, ord);
    if (!vd) {
        fprintf(stderr, "Error: no se pudo crear el VD.\n");
        return 1;
    }

    int op;
    do {
        menu();
        op = pedir_int("Opcion: ");
        switch (op) {
        case 1: {
            int v = pedir_int("Valor a anadir: ");
            anadir_vd(vd, v);
        }
        break;
        case 2: {
            int i = pedir_int("Indice a eliminar: ");
            eliminar_vd(vd, i);
        }
        break;
        case 3: {
            int v = pedir_int("Valor a buscar: ");
            printf("Indice: %d\n", buscar_vd(vd, v));
        }
        break;
        case 4:
            imprimir_vd(vd);
            break;
        case 5:
            printf("Capacidad: %d\n", tamano_vd(vd));
            break;
        case 6:
            printf("Cantidad: %d\n", cantidad_vd(vd));
            break;
        case 7: {
            int i = pedir_int("Indice: ");
            printf("vd[%d] = %d\n", i, acceder_vd(vd, i));
        }
        break;
        case 8: {
            int i = pedir_int("Indice: ");
            printf("vd[%d] (verif) = %d\n", i, acceder_verificado_vd(vd, i));
        }
        break;
        case 9:
            break;
        default:
            printf("Opcion invalida.\n");
        }
    } while (op != 9);

    destruir_vd( & vd);
    return 0;
}