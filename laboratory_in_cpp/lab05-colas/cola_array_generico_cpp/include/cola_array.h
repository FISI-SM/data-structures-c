#ifndef COLA_ARRAY_H
#define COLA_ARRAY_H

#include <stdexcept>
#include <iostream>
using namespace std;

// Cola genérica basada en arreglo dinámico con buffer circular
template <typename T>
struct ColaArray {
    T* datos;
    size_t n;     // número de elementos
    size_t cap;   // capacidad
    size_t head;  // índice del frente
    size_t tail;  // índice de la posición libre después del último

    ColaArray(size_t capacidad_inicial = 8) {
        if (capacidad_inicial == 0) capacidad_inicial = 1;
        datos = new T[capacidad_inicial];
        n = 0; cap = capacidad_inicial; head = 0; tail = 0;
    }

    // Regla de 3
    ColaArray(const ColaArray& o) {
        datos = new T[o.cap];
        n = o.n; cap = o.cap; head = 0; tail = n;
        for (size_t i = 0; i < n; ++i) datos[i] = o.datos[(o.head + i) % o.cap];
    }

    ColaArray& operator=(ColaArray o) {
        swap(datos, o.datos);
        swap(n, o.n);
        swap(cap, o.cap);
        swap(head, o.head);
        swap(tail, o.tail);
        return *this;
    }

    ~ColaArray() { delete[] datos; }

    bool empty() const { return n == 0; }
    size_t size() const { return n; }
    size_t capacity() const { return cap; }

    void clear() { n = 0; head = 0; tail = 0; }

    void reservar(size_t m) {
        if (m <= cap) return;
        T* nd = new T[m];
        for (size_t i = 0; i < n; ++i) nd[i] = datos[(head + i) % cap];
        delete[] datos;
        datos = nd;
        cap = m;
        head = 0;
        tail = n;
    }

    void push(const T& x) {
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

    T& front() {
        if (empty()) throw runtime_error("front() en cola vacia");
        return datos[head];
    }

    const T& front() const {
        if (empty()) throw runtime_error("front() en cola vacia");
        return datos[head];
    }

    T& back() {
        if (empty()) throw runtime_error("back() en cola vacia");
        return datos[(tail + cap - 1) % cap];
    }

    const T& back() const {
        if (empty()) throw runtime_error("back() en cola vacia");
        return datos[(tail + cap - 1) % cap];
    }

    void imprimir() const {
        cout << "Cola[front->back]: ";
        for (size_t i = 0; i < n; ++i) {
            cout << datos[(head + i) % cap] << " ";
        }
        cout << "\n";
    }
};

#endif
