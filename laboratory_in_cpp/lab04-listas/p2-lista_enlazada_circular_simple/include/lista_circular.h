#ifndef LISTA_CIRCULAR_H
#define LISTA_CIRCULAR_H

#include <iostream>
using namespace std;

// Nodo circular simple
struct Nodo {
    int dato;
    Nodo* sig;

    // Constructor con "{}"
    Nodo(int v) {
        dato = v;
        sig  = nullptr;
    }
};

// Lista circular con puntero al último (cola)
struct ListaCircular {
    Nodo* ultimo;  // si es nullptr, lista vacía. Si no, ultimo->sig es el "primero"

    // constructor
    ListaCircular() { ultimo = nullptr; }

    // Inserciones
    void insertarInicio(int valor);
    void insertarFinal(int valor);

    // Eliminaciones
    bool eliminarInicio();
    bool eliminarFinal();
    bool eliminarValor(int v);

    // Utilidades
    Nodo* buscar(int valor);
    int   tamano() const;
    void  imprimir() const;
    void  liberar();

    //destructor
    ~ListaCircular() { liberar(); }
};

#endif
