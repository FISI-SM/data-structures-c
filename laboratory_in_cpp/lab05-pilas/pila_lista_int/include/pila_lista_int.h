#ifndef PILA_LISTA_INT_H
#define PILA_LISTA_INT_H

#include <iostream>
#include <stdexcept>
using namespace std;

struct NodoPila {
    int dato;
    NodoPila* sig;
    NodoPila(int v) : dato(v), sig(nullptr) {}
};

struct PilaListaInt {
    NodoPila* tope;
    int n;

    PilaListaInt() : tope(nullptr), n(0) {}
    ~PilaListaInt() { clear(); }

    bool empty() const { return tope == nullptr; }
    int  size()  const { return n; }

    void push(int x) {
        NodoPila* nuevo = new NodoPila(x);
        nuevo->sig = tope;
        tope = nuevo;
        ++n;
    }

    void pop() {
        if (empty()) throw runtime_error("pop() en pila vacia");
        NodoPila* viejo = tope;
        tope = tope->sig;
        delete viejo;
        --n;
    }

    int& top() {
        if (empty()) throw runtime_error("top() en pila vacia");
        return tope->dato;
    }

    const int& top() const {
        if (empty()) throw runtime_error("top() en pila vacia");
        return tope->dato;
    }

    void clear() {
        while (!empty()) pop();
    }

    void imprimir() const {
        cout << "PilaListaInt[top->bottom]: ";
        for (NodoPila* cur = tope; cur; cur = cur->sig) cout << cur->dato << " ";
        cout << "\n";
    }
};

#endif
