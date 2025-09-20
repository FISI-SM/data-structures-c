#ifndef LISTA_DOBLE_H
#define LISTA_DOBLE_H

#include <iostream>
using namespace std;

struct Nodo {
    int dato;
    Nodo* ant;
    Nodo* sig;

    Nodo(int v) {
        dato = v;
        ant  = nullptr;
        sig  = nullptr;
    }
};

struct ListaDoble {
    Nodo* cabeza;
    Nodo* cola;

    ListaDoble() { cabeza = nullptr; cola = nullptr; }

    void insertarInicio(int v);
    void insertarFinal(int v);

    bool eliminarInicio();
    bool eliminarFinal();
    bool eliminarValor(int v);

    Nodo* buscar(int v);
    int   tamano() const;
    void  imprimir() const;
    void  imprimirReversa() const;
    void  liberar();

    ~ListaDoble() { liberar(); }
};

#endif
