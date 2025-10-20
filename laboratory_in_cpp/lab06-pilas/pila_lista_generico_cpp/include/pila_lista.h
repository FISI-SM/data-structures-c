#ifndef PILA_LISTA_H
#define PILA_LISTA_H

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

// Pila implementada con lista enlazada simple
template <typename T>
struct PilaLista {
    Nodo<T>* tope;
    size_t n;

    PilaLista() : tope(nullptr), n(0) {}

    ~PilaLista() { clear(); }

    void push(const T& x) {
        Nodo<T>* nuevo = new Nodo<T>(x);
        nuevo->sig = tope;
        tope = nuevo;
        ++n;
    }

    void pop() {
        if (empty()) throw runtime_error("pop() en pila vacia");
        Nodo<T>* viejo = tope;
        tope = tope->sig;
        delete viejo;
        --n;
    }

    T& top() {
        if (empty()) throw runtime_error("top() en pila vacia");
        return tope->dato;
    }

    const T& top() const {
        if (empty()) throw runtime_error("top() en pila vacia");
        return tope->dato;
    }

    bool empty() const { return tope == nullptr; }
    size_t size() const { return n; }

    void clear() {
        while (!empty()) pop();
    }

    void imprimir() const {
        cout << "Pila[top->bottom]: ";
        for (Nodo<T>* cur = tope; cur; cur = cur->sig) {
            cout << cur->dato << " ";
        }
        cout << "\n";
    }
};

#endif
