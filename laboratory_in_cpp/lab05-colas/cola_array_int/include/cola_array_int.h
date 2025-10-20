#ifndef COLA_ARRAY_INT_H
#define COLA_ARRAY_INT_H

#include <stdexcept>
#include <iostream>
using namespace std;

struct ColaArrayInt {
    int* datos;
    int n;     // número de elementos
    int cap;   // capacidad
    int head;  // índice del frente
    int tail;  // índice siguiente al último

    // Constructor
    ColaArrayInt(int capacidad_inicial = 8);

    // Regla de 3
    ColaArrayInt(const ColaArrayInt& o);
    ColaArrayInt& operator=(ColaArrayInt o);
    ~ColaArrayInt();

    // Métodos
    bool empty() const;
    int  size()  const;
    int  capacity() const;
    void clear();
    void reservar(int m);
    void push(int x);
    void pop();

    int& front();
    const int& front() const;

    int& back();
    const int& back() const;

    void imprimir() const;
};

#endif
