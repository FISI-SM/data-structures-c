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
    int tam;   // contador de elementos

    // Constructor
    Lista() {
        cabeza = nullptr;
        tam = 0;
    }

    // ---- Declaraciones que usas en el .cpp ----
    void insertarInicio(int valor);
    void insertarFinal(int valor);
    void eliminar(int valor);
    Nodo* buscar(int valor);
    void imprimir();
    void liberar();

    int tamano();  // <- usado en tu .cpp

    // Nuevos que agregaste en el .cpp
    void AdicionaAPosicion(int dato, int posicion);
    int  RetiraDePosicion(int posicion);

    ~Lista() { liberar(); }
};

#endif
