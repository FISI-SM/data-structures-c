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

    ColaArrayInt(int capacidad_inicial = 8) {
        if (capacidad_inicial <= 0) capacidad_inicial = 1;
        datos = new int[capacidad_inicial];
        n = 0; cap = capacidad_inicial; head = 0; tail = 0;
    }

    // regla de 3
    ColaArrayInt(const ColaArrayInt& o) {
        datos = new int[o.cap];
        n = o.n; cap = o.cap; head = 0; tail = n;
        for (int i = 0; i < n; ++i) datos[i] = o.datos[(o.head + i) % o.cap];
    }

    ColaArrayInt& operator=(ColaArrayInt o) {
        swap(datos, o.datos);
        swap(n, o.n);
        swap(cap, o.cap);
        swap(head, o.head);
        swap(tail, o.tail);
        return *this;
    }

    ~ColaArrayInt() { delete[] datos; }

    bool empty() const { return n == 0; }
    int  size()  const { return n; }
    int  capacity() const { return cap; }

    void clear() { n = 0; head = 0; tail = 0; }

    void reservar(int m) {
        if (m <= cap) return;
        int* nd = new int[m];
        for (int i = 0; i < n; ++i) nd[i] = datos[(head + i) % cap];
        delete[] datos;
        datos = nd;
        cap = m;
        head = 0;
        tail = n;
    }

    void push(int x) {
        if (n == cap) reservar(cap * 2);
        datos[tail] = x;
        tail = (tail + 1) % cap;
        ++n;
    }

    void pop() {
        if (empty()) throw runtime_error("pop() en cola vacia");
        head = (head + 1) % cap;
        --n;
    }

    int& front() {
        if (empty()) throw runtime_error("front() en cola vacia");
        return datos[head];
    }

    const int& front() const {
        if (empty()) throw runtime_error("front() en cola vacia");
        return datos[head];
    }

    int& back() {
        if (empty()) throw runtime_error("back() en cola vacia");
        return datos[(tail + cap - 1) % cap];
    }

    const int& back() const {
        if (empty()) throw runtime_error("back() en cola vacia");
        return datos[(tail + cap - 1) % cap];
    }

    void imprimir() const {
        cout << "ColaArrayInt[front->back]: ";
        for (int i = 0; i < n; ++i) cout << datos[(head + i) % cap] << " ";
        cout << "\n";
    }
};

#endif
