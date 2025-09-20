#ifndef COLA_LISTA_INT_H
#define COLA_LISTA_INT_H

#include <stdexcept>
#include <iostream>
using namespace std;

struct NodoCola {
    int dato;
    NodoCola* sig;
    NodoCola(int v) : dato(v), sig(nullptr) {}
};

struct ColaListaInt {
    NodoCola* frente;
    NodoCola* fondo;
    int n;

    ColaListaInt() : frente(nullptr), fondo(nullptr), n(0) {}
    ~ColaListaInt() { clear(); }

    bool empty() const { return n == 0; }
    int  size()  const { return n; }

    void push(int x) {
        NodoCola* nuevo = new NodoCola(x);
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
        NodoCola* viejo = frente;
        frente = frente->sig;
        if (!frente) fondo = nullptr;
        delete viejo;
        --n;
    }

    int& front() {
        if (empty()) throw runtime_error("front() en cola vacia");
        return frente->dato;
    }

    const int& front() const {
        if (empty()) throw runtime_error("front() en cola vacia");
        return frente->dato;
    }

    int& back() {
        if (empty()) throw runtime_error("back() en cola vacia");
        return fondo->dato;
    }

    const int& back() const {
        if (empty()) throw runtime_error("back() en cola vacia");
        return fondo->dato;
    }

    void clear() {
        while (!empty()) pop();
    }

    void imprimir() const {
        cout << "ColaListaInt[front->back]: ";
        for (NodoCola* cur = frente; cur; cur = cur->sig) cout << cur->dato << " ";
        cout << "\n";
    }
};

#endif
