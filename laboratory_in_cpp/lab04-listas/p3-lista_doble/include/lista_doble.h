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

    ListaDoble() { cabeza = cola = nullptr; }

    // --- Operaciones previas ---
    void AdicionarAlInicioDoble(int v);
    void AdicionarDoble(int v);
    void AdicionarEnPosicionDoble(int v, int posicion);
    void AdicionarEnOrdenDoble(int v);
    bool RetiraDoInicioDuplo();
    bool RetiraDoble();
    bool RetiraEspecificoDoble(int v);
    bool RetiraDeLaPosicionDoble(int posicion);
    Nodo* buscar(int v);
    int tamano() const;
    void imprimir() const;
    void imprimirReversa() const;
    void liberar();

    // --- NUEVAS operaciones ---
    bool ListaVaciaDoble() const;
    int PosicionDoble(int v) const;
    bool ContieneDoble(int v) const;
    void CreaListaDoble();
    void DestruyeListaDoble();

    ~ListaDoble() { liberar(); }
};


#endif
