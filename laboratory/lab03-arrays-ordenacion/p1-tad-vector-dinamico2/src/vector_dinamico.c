#include "vector_dinamico.h"

#include <stdio.h>

#include <stdlib.h>

struct vd {
    bool ordenado;
    int tamano;
    int cantidad;
    int *datos;
};

static inline bool esta_lleno_vd(const VD *vd) {
    return vd->cantidad == vd->tamano;
}

static int agrandar(VD *vd) {
    int nuevo = vd->tamano > 0 ? vd->tamano * 2 : 4;
    int *p = (int *) realloc(vd->datos, (size_t) nuevo *sizeof(int));
    if (!p) return -1;
    vd->datos = p;
    vd->tamano = nuevo;
    return 0;
}

static int reducir_si_corresponde(VD *vd) {
    if (vd->tamano >= 4 && vd->cantidad < vd->tamano / 4) {
        int nuevo = vd->tamano / 2;
        if (nuevo < 4) nuevo = 4;
        if (vd->cantidad > nuevo) return 0;
        int *p = (int *) realloc(vd->datos, (size_t) nuevo *sizeof(int));
        if (!p) return -1;
        vd->datos = p;
        vd->tamano = nuevo;
    }
    return 0;
}

static int busqueda_binaria_iterativa(const int *a, int n, int x) {
    int i = 0, j = n - 1;
    while (i <= j) {
        int m = i + (j - i) / 2;
        if (a[m] == x) return m;
        if (a[m] < x) i = m + 1;
        else j = m - 1;
    }
    return -1;
}

static int busqueda_secuencial(const VD *vd, int x) {
    for (int i = 0; i < vd->cantidad; ++i)
        if (vd->datos[i] == x) return i;
    return -1;
}

VD *crear_vd(int tamano_inicial, bool ordenado) {
    if (tamano_inicial <= 0) tamano_inicial = 4;
    VD *vd = (VD *) malloc(sizeof *vd);
    if (!vd) return NULL;
    vd->datos = (int *) calloc((size_t) tamano_inicial, sizeof(int));
    if (!vd->datos) {
        free(vd);
        return NULL;
    }
    vd->tamano = tamano_inicial;
    vd->cantidad = 0;
    vd->ordenado = ordenado;
    return vd;
}

void destruir_vd(VD ** pp) {
    if (!pp || ! *pp) return;
    VD *vd = *pp;
    free(vd->datos);
    free(vd);* pp = NULL;
}

void imprimir_vd(const VD *vd) {
    printf("vector(indice = valor) = { ");
    for (int i = 0; i < vd->cantidad; ++i) {
        printf("%d = %d", i, vd->datos[i]);
        if (i + 1 < vd->cantidad) printf(" | ");
    }
    printf(" }\n");
}

void anadir_vd(VD *vd, int valor) {
    if (esta_lleno_vd(vd)) {
        if (agrandar(vd) != 0) {
            fprintf(stderr, "Error: no se pudo agrandar el vector.\n");
            return;
        }
    }
    if (vd->ordenado) {
        int i = vd->cantidad - 1;
        while (i >= 0 && vd->datos[i] > valor) {
            vd->datos[i + 1] = vd->datos[i];
            --i;
        }
        vd->datos[i + 1] = valor;
        vd->cantidad++;
    } else {
        vd->datos[vd->cantidad++] = valor;
    }
}

int buscar_vd(const VD *vd, int valor) {
    return vd->ordenado ? busqueda_binaria_iterativa(vd->datos, vd->cantidad, valor) :
        busqueda_secuencial(vd, valor);
}

void eliminar_vd(VD *vd, int index) {
    if (index < 0 || index >= vd->cantidad) return;
    if (vd->ordenado) {
        for (int i = index; i + 1 < vd->cantidad; ++i) 
            vd->datos[i] = vd->datos[i + 1];
        vd->cantidad--;
    } else {
        vd->datos[index] = vd->datos[vd->cantidad - 1];
        vd->cantidad--;
    }
    if (reducir_si_corresponde(vd) != 0) 
        fprintf(stderr, "Advertencia: no se pudo reducir el vector.\n");
}

int acceder_vd(const VD *vd, int index) {
    return vd->datos[index];
}
int acceder_verificado_vd(const VD *vd, int index) {
    return (index >= 0 && index < vd->cantidad) ? vd->datos[index] : -1;
}
int tamano_vd(const VD *vd) {
    return vd->tamano;
}
int cantidad_vd(const VD *vd) {
    return vd->cantidad;
}