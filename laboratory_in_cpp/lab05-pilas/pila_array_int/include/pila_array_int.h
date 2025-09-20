#ifndef PILA_ARRAY_INT_H
#define PILA_ARRAY_INT_H

#include <stdexcept>
#include <iostream>
using namespace std;

struct PilaArrayInt {
    int* datos;
    int  n;    // cantidad de elementos
    int  cap;  // capacidad

    PilaArrayInt(int capacidad_inicial = 8) {
        if (capacidad_inicial <= 0) capacidad_inicial = 1;
        datos = new int[capacidad_inicial];
        n = 0; cap = capacidad_inicial;
    }

    // Regla de 3
    PilaArrayInt(const PilaArrayInt& o) {
        datos = new int[o.cap];
        n = o.n; cap = o.cap;
        for (int i = 0; i < n; ++i) datos[i] = o.datos[i];
    }

    PilaArrayInt& operator=(PilaArrayInt o) {
        swap(datos, o.datos);
        swap(n, o.n);
        swap(cap, o.cap);
        return *this;
    }

    ~PilaArrayInt() { delete[] datos; }

    bool empty() const { return n == 0; }
    int  size()  const { return n; }
    int  capacity() const { return cap; }

    void clear() { n = 0; }

    void reservar(int m) {
        if (m <= cap) return;
        int* nd = new int[m];
        for (int i = 0; i < n; ++i) nd[i] = datos[i];
        delete[] datos;
        datos = nd;
        cap = m;
    }

    void push(int x) {
        if (n == cap) reservar(cap * 2);
        datos[n++] = x;
    }

    void pop() {
        if (empty()) throw runtime_error("pop() en pila vacia");
        --n;
    }

    int& top() {
        if (empty()) throw runtime_error("top() en pila vacia");
        return datos[n-1];
    }

    const int& top() const {
        if (empty()) throw runtime_error("top() en pila vacia");
        return datos[n-1];
    }

    void imprimir() const {
        cout << "PilaArrayInt[top->bottom]: ";
        for (int i = n-1; i >= 0; --i) cout << datos[i] << " ";
        cout << "\n";
    }
};

#endif
