#ifndef PILA_ARRAY_H
#define PILA_ARRAY_H

#include <stdexcept>
#include <iostream>
#include <utility>   // std::swap
using namespace std;

// Pila genérica implementada con arreglo dinámico 'new[]' (sin std::vector)
template <typename T>
struct PilaArray {
    T*     datos;
    size_t n;        // cantidad de elementos
    size_t cap;      // capacidad actual

    // --- Constructores / Regla de 3 ---
    PilaArray(size_t capacidad_inicial = 8) {
        if (capacidad_inicial == 0) capacidad_inicial = 1;
        datos = new T[capacidad_inicial];
        n  = 0;
        cap = capacidad_inicial;
    }

    // Copy constructor
    PilaArray(const PilaArray& other) {
        datos = new T[other.cap];
        n  = other.n;
        cap = other.cap;
        for (size_t i = 0; i < n; ++i) datos[i] = other.datos[i];
    }

    // Copy assignment
    PilaArray& operator=(PilaArray other) {
        swap(datos, other.datos);
        swap(n, other.n);
        swap(cap, other.cap);
        return *this;
    }

    // Destructor
    ~PilaArray() {
        delete[] datos;
    }

    // --- Operaciones básicas ---
    void push(const T& x) {
        if (n == cap) reservar(cap * 2);
        datos[n++] = x;
    }

    void pop() {
        if (empty()) throw runtime_error("pop() en pila vacia");
        --n;
    }

    T& top() {
        if (empty()) throw runtime_error("top() en pila vacia");
        return datos[n-1];
    }

    const T& top() const {
        if (empty()) throw runtime_error("top() en pila vacia");
        return datos[n-1];
    }

    bool empty() const { return n == 0; }
    size_t size() const { return n; }
    size_t capacity() const { return cap; }

    void clear() { n = 0; }

    // Reserva capacidad al menos 'm'; preserva elementos
    void reservar(size_t m) {
        if (m <= cap) return;
        T* nuevo = new T[m];
        for (size_t i = 0; i < n; ++i) nuevo[i] = datos[i];
        delete[] datos;
        datos = nuevo;
        cap = m;
    }

    // Reduce capacidad para ajustarse (opcional)
    void shrink_to_fit() {
        if (cap == n) return;
        if (n == 0) {
            delete[] datos;
            datos = new T[1];
            cap = 1;
            return;
        }
        T* nuevo = new T[n];
        for (size_t i = 0; i < n; ++i) nuevo[i] = datos[i];
        delete[] datos;
        datos = nuevo;
        cap = n;
    }

    void imprimir() const {
        cout << "Pila[top->bottom]: ";
        for (size_t i = n; i > 0; --i) cout << datos[i-1] << " ";
        cout << "\n";
    }
};

#endif
