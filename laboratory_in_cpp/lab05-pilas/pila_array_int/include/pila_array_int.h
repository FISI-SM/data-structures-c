#ifndef PILA_ARRAY_INT_H
#define PILA_ARRAY_INT_H

#include <stdexcept>
#include <iostream>
using namespace std;

struct PilaArrayInt {
    int* datos;
    int  n;    // cantidad de elementos
    int  cap;  // capacidad

    // Constructor
    PilaArrayInt(int capacidad_inicial = 8);

    // Regla de 3
    PilaArrayInt(const PilaArrayInt& o);
    PilaArrayInt& operator=(PilaArrayInt o);
    ~PilaArrayInt();

    // Métodos
    bool empty() const;
    int  size()  const;
    int  capacity() const;
    void clear();
    void reservar(int m);
    void push(int x);
    void pop();
    int& top();
    const int& top() const;
    void imprimir() const;
};

#endif
