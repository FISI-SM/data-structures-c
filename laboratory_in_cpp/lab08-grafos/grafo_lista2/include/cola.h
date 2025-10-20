#ifndef COLA_H
#define COLA_H

#include <stdexcept>
#include <iostream>
using namespace std;

struct NodoCola {
    int dato;
    NodoCola* sig;
    NodoCola(int v);
};

struct Cola {
    NodoCola* frente;
    NodoCola* fondo;
    int n;

    Cola();
    ~Cola();

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
