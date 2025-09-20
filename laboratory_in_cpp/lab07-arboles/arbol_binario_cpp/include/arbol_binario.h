#ifndef ARBOL_BINARIO_H
#define ARBOL_BINARIO_H

#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

struct Nodo {
    int dato;
    Nodo* izq;
    Nodo* der;

    // Constructor con "{}"
    Nodo(int v) {
        dato = v;
        izq = nullptr;
        der = nullptr;
    }
};

struct ArbolBinario {
    Nodo* raiz;

    ArbolBinario() { raiz = nullptr; }

    // Construcción manual (para demo): insertar como árbol completo por niveles
    // (NO es ABB). Inserta por el primer hueco en nivel-orden.
    void insertarCompleto(int v);

    // Recorridos
    void preorden() const;
    void inorden() const;
    void postorden() const;
    void porNiveles() const;

    // Métricas
    int altura() const;        // número de niveles (árbol vacío = 0)
    int contarNodos() const;

    // Transformaciones/Utilidades
    void reflejar();           // espejo
    void liberar();            // free total

    // Helpers privados
private:
    void preordenRec(Nodo* n) const;
    void inordenRec(Nodo* n) const;
    void postordenRec(Nodo* n) const;
    int  alturaRec(Nodo* n) const;
    int  contarRec(Nodo* n) const;
    void reflejarRec(Nodo* n);
    void liberarRec(Nodo* n);
};

#endif
