#ifndef PILA_LISTA_INT_H
#define PILA_LISTA_INT_H

#include <iostream>
#include <stdexcept>
using namespace std;

struct NodoPila {
    int dato;
    NodoPila* sig;
    NodoPila(int v);
};

struct PilaListaInt {
    NodoPila* tope;
    int n;

    PilaListaInt();
    ~PilaListaInt();

    bool empty() const;
    int  size()  const;

    void push(int x);
    void pop();

    int& top();
    const int& top() const;

    void clear();
    void imprimir() const;
};

#endif
