#ifndef LISTA_DOBLE_CIRCULAR_H
#define LISTA_DOBLE_CIRCULAR_H

#include <iostream>
using namespace std;

struct Nodo {
    int dato;
    Nodo* ant;
    Nodo* sig;

    // Constructor con "{}"
    Nodo(int v) {
        dato = v;
        ant  = nullptr;
        sig  = nullptr;
    }
};

// Lista doblemente enlazada circular manteniendo puntero al ultimo.
// Si 'ultimo' es nullptr, la lista esta vacia.
// El primer nodo logico es ultimo->sig; el ultimo es 'ultimo'.
struct ListaDobleCircular {
    Nodo* ultimo;

    ListaDobleCircular() { ultimo = nullptr; }

    // Inserciones
    void insertarInicio(int v); // inserta antes del primero logico
    void insertarFinal(int v);  // inserta despues del ultimo y actualiza 'ultimo'

    // Eliminaciones
    bool eliminarInicio();      // elimina el primero logico
    bool eliminarFinal();       // elimina el ultimo logico
    bool eliminarValor(int v);  // elimina primera ocurrencia

    // Utilidades
    Nodo* buscar(int v);        // retorna puntero al nodo o nullptr
    int   tamano() const;
    void  imprimir() const;           // recorre hacia adelante
    void  imprimirReversa() const;    // recorre hacia atras desde 'ultimo'
    void  liberar();

    ~ListaDobleCircular() { liberar(); }
};

#endif
