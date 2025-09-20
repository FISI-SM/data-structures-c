#ifndef ABB_H
#define ABB_H

#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

struct NodoABB {
    int dato;
    NodoABB* izq;
    NodoABB* der;

    NodoABB(int v) {
        dato = v;
        izq = nullptr;
        der = nullptr;
    }
};

struct ABB {
    NodoABB* raiz;

    ABB() { raiz = nullptr; }

    // Operaciones básicas
    void insertar(int v);
    bool contiene(int v) const;
    bool eliminar(int v);           // retorna true si se eliminó

    // Búsqueda de mínimo/máximo
    int minimo() const;             // lanza si vacío
    int maximo() const;             // lanza si vacío

    // Recorridos
    void inorden() const;
    void preorden() const;
    void postorden() const;
    void porNiveles() const;

    // Métricas y limpieza
    int altura() const;
    void liberar();

private:
    NodoABB* insertarRec(NodoABB* n, int v);
    bool contieneRec(NodoABB* n, int v) const;
    NodoABB* eliminarRec(NodoABB* n, int v, bool& borrado);
    NodoABB* minNode(NodoABB* n) const;
    int alturaRec(NodoABB* n) const;
    void inordenRec(NodoABB* n) const;
    void preordenRec(NodoABB* n) const;
    void postordenRec(NodoABB* n) const;
    void liberarRec(NodoABB* n);
};

#endif
