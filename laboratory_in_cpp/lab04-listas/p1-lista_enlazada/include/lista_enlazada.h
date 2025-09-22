#ifndef LISTA_ENLAZADA_H
#define LISTA_ENLAZADA_H

#include <iostream>
using namespace std;

// Nodo con constructor
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
    int tam;

    // Constructor
    Lista() {
        cabeza = nullptr;
        tam = 0;
    }

    // Métodos
    void insertarInicio(int valor);
    void insertarFinal(int valor);
    void eliminar(int valor);
    Nodo* buscar(int valor);
    void imprimir();
    void liberar();
    int tamano();
    void AdicionaAPosición(int dato, int posicion);
    int RetiraDePosicion(int posicion) {


    // Destructor
    ~Lista() { liberar(); }
};

#endif
