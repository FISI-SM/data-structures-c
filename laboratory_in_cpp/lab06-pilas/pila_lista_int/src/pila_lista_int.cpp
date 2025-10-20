#include "pila_lista_int.h"

PilaListaInt::~PilaListaInt() {
    clear();
}

bool PilaListaInt::empty() const {
    return tope == nullptr;
}
int PilaListaInt::size() const {
    return n;
}

void PilaListaInt::push(int x) {
    NodoPila * nuevo = new NodoPila(x);
    nuevo -> sig = tope;
    tope = nuevo;
    ++n;
}

void PilaListaInt::pop() {
    if (empty()) 
        throw runtime_error("pop() en pila vacia");
    NodoPila * viejo = tope;
    tope = tope -> sig;
    delete viejo;
    --n;
}

int & PilaListaInt::top() {
    if (empty()) 
        throw runtime_error("top() en pila vacia");
    return tope -> dato;
}

const int & PilaListaInt::top() const {
    if (empty()) 
        throw runtime_error("top() en pila vacia");
    return tope -> dato;
}

void PilaListaInt::clear() {
    while (!empty()) 
        pop();
}

void PilaListaInt::imprimir() const {
    cout << "PilaListaInt[top->bottom]: ";
    for (NodoPila * cur = tope; cur; cur = cur -> sig) {
        cout << cur -> dato << " ";
    }
    cout << "\n";
}