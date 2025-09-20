#include "cola_lista_int.h"

// ================= NodoCola =================
NodoCola::NodoCola(int v) : dato(v), sig(nullptr) {}

// ================= ColaListaInt =================
ColaListaInt::ColaListaInt() : frente(nullptr), fondo(nullptr), n(0) {}

ColaListaInt::~ColaListaInt() { clear(); }

bool ColaListaInt::empty() const { return n == 0; }
int  ColaListaInt::size()  const { return n; }

void ColaListaInt::push(int x) {
    NodoCola* nuevo = new NodoCola(x);
    if (empty()) {
        frente = fondo = nuevo;
    } else {
        fondo->sig = nuevo;
        fondo = nuevo;
    }
    ++n;
}

void ColaListaInt::pop() {
    if (empty()) throw runtime_error("pop() en cola vacia");
    NodoCola* viejo = frente;
    frente = frente->sig;
    if (!frente) fondo = nullptr;
    delete viejo;
    --n;
}

int& ColaListaInt::front() {
    if (empty()) throw runtime_error("front() en cola vacia");
    return frente->dato;
}

const int& ColaListaInt::front() const {
    if (empty()) throw runtime_error("front() en cola vacia");
    return frente->dato;
}

int& ColaListaInt::back() {
    if (empty()) throw runtime_error("back() en cola vacia");
    return fondo->dato;
}

const int& ColaListaInt::back() const {
    if (empty()) throw runtime_error("back() en cola vacia");
    return fondo->dato;
}

void ColaListaInt::clear() {
    while (!empty()) pop();
}

void ColaListaInt::imprimir() const {
    cout << "ColaListaInt[front->back]: ";
    for (NodoCola* cur = frente; cur; cur = cur->sig) {
        cout << cur->dato << " ";
    }
    cout << "\n";
}
