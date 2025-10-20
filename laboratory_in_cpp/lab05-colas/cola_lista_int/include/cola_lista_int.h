#ifndef COLA_LISTA_INT_H
#define COLA_LISTA_INT_H

#include <stdexcept>
#include <iostream>
using namespace std;

struct NodoCola {
    int dato;
    NodoCola* sig;
    NodoCola(int v);
};

struct ColaListaInt {
    NodoCola* frente;
    NodoCola* fondo;
    int n;

    ColaListaInt();
    ~ColaListaInt();

    bool empty() const;
    int  size()  const;

    void push(int x);
    void pop();

    int& front();
    const int& front() const;

    int& back();
    const int& back() const;

    void clear();
    void imprimir() const;
};

#endif
