#include "cola.h"

// ================= NodoCola =================
NodoCola::NodoCola(int v) : dato(v), sig(nullptr) {}

// ================= Cola =================
Cola::Cola() : frente(nullptr), fondo(nullptr), n(0) {}

Cola::~Cola() { clear(); }

bool Cola::empty() const { return n == 0; }
int  Cola::size()  const { return n; }

void Cola::push(int x) {
    NodoCola* nuevo = new NodoCola(x);
    if (empty()) {
        frente = fondo = nuevo;
    } else {
        fondo->sig = nuevo;
        fondo = nuevo;
    }
    ++n;
}

void Cola::pop() {
    if (empty()) throw runtime_error("pop() en cola vacia");
    NodoCola* viejo = frente;
    frente = frente->sig;
    if (!frente) fondo = nullptr;
    delete viejo;
    --n;
}

int& Cola::front() {
    if (empty()) throw runtime_error("front() en cola vacia");
    return frente->dato;
}

const int& Cola::front() const {
    if (empty()) throw runtime_error("front() en cola vacia");
    return frente->dato;
}

int& Cola::back() {
    if (empty()) throw runtime_error("back() en cola vacia");
    return fondo->dato;
}

const int& Cola::back() const {
    if (empty()) throw runtime_error("back() en cola vacia");
    return fondo->dato;
}

void Cola::clear() {
    while (!empty()) pop();
}

void Cola::imprimir() const {
    cout << "Cola[front->back]: ";
    for (NodoCola* cur = frente; cur; cur = cur->sig) {
        cout << cur->dato << " ";
    }
    cout << "\n";
}
