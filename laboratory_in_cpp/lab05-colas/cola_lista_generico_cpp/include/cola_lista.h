#ifndef COLA_LISTA_H
#define COLA_LISTA_H

#include <iostream>
#include <stdexcept>
using namespace std;

// Nodo para lista enlazada
template <typename T>
struct Nodo {
    T dato;
    Nodo* sig;
    Nodo(const T& v) : dato(v), sig(nullptr) {}
};

// Cola basada en lista enlazada simple: O(1) en push y pop
template <typename T>
struct ColaLista {
    Nodo<T>* frente; // front
    Nodo<T>* fondo;  // back
    size_t n;

    ColaLista() : frente(nullptr), fondo(nullptr), n(0) {}
    ~ColaLista() { clear(); }

    bool empty() const { return n == 0; }
    size_t size() const { return n; }

    void push(const T& x) {
        Nodo<T>* nuevo = new Nodo<T>(x);
        if (empty()) {
            frente = fondo = nuevo;
        } else {
            fondo->sig = nuevo;
            fondo = nuevo;
        }
        ++n;
    }

    void pop() {
        if (empty()) throw runtime_error("pop() en cola vacia");
        Nodo<T>* viejo = frente;
        frente = frente->sig;
        if (!frente) fondo = nullptr;
        delete viejo;
        --n;
    }

    T& front() {
        if (empty()) throw runtime_error("front() en cola vacia");
        return frente->dato;
    }

    const T& front() const {
        if (empty()) throw runtime_error("front() en cola vacia");
        return frente->dato;
    }

    T& back() {
        if (empty()) throw runtime_error("back() en cola vacia");
        return fondo->dato;
    }

    const T& back() const {
        if (empty()) throw runtime_error("back() en cola vacia");
        return fondo->dato;
    }

    void clear() {
        while (!empty()) pop();
    }

    void imprimir() const {
        cout << "Cola[front->back]: ";
        for (Nodo<T>* cur = frente; cur; cur = cur->sig)
            cout << cur->dato << " ";
        cout << "\n";
    }
};

#endif
