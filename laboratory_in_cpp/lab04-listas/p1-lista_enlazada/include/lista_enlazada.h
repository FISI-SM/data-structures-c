#ifndef LISTA_ENLAZADA_H
#define LISTA_ENLAZADA_H

#include <iostream>
using namespace std;

// Nodo con constructor usando "{}"
struct Nodo {
    int dato;
    Nodo* sig;

    Nodo(int v) {
        dato = v;
        sig = nullptr;
    }
};

// Lista enlazada simple
struct Lista {
    Nodo* cabeza;

    Lista() { cabeza = nullptr; }

    void insertarInicio(int valor);
    void insertarFinal(int valor);
    void eliminar(int valor);
    Nodo* buscar(int valor);
    void imprimir();
    void liberar();

    ~Lista() { liberar(); }
};

#endif
