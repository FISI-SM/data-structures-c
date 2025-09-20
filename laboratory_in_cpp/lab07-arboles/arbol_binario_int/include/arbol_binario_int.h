#ifndef ARBOL_BINARIO_INT_H
#define ARBOL_BINARIO_INT_H
#include <iostream>
#include <queue>
using namespace std;

struct Nodo {
    int dato;
    Nodo* izq;
    Nodo* der;
    Nodo(int v) : dato(v), izq(nullptr), der(nullptr) {}
};

struct ArbolBinario {
    Nodo* raiz;
    ArbolBinario() : raiz(nullptr) {}
    void insertarCompleto(int v);
    void preorden() const;  void inorden() const;  void postorden() const;  void porNiveles() const;
    int altura() const;     int contarNodos() const;
    void reflejar();        void liberar();
private:
    void preRec(Nodo*) const; void inRec(Nodo*) const; void postRec(Nodo*) const;
    int altRec(Nodo*) const;  int cntRec(Nodo*) const; void refRec(Nodo*);
    void freeRec(Nodo*);
};
#endif
