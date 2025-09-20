#include "pila_array_int.h"
#include <algorithm> // para swap

PilaArrayInt::PilaArrayInt(int capacidad_inicial) {
    if (capacidad_inicial <= 0) capacidad_inicial = 1;
    datos = new int[capacidad_inicial];
    n = 0;
    cap = capacidad_inicial;
}

PilaArrayInt::PilaArrayInt(const PilaArrayInt& o) {
    datos = new int[o.cap];
    n = o.n;
    cap = o.cap;
    for (int i = 0; i < n; ++i) datos[i] = o.datos[i];
}

PilaArrayInt& PilaArrayInt::operator=(PilaArrayInt o) {
    swap(datos, o.datos);
    swap(n, o.n);
    swap(cap, o.cap);
    return *this;
}

PilaArrayInt::~PilaArrayInt() {
    delete[] datos;
}

bool PilaArrayInt::empty() const { return n == 0; }
int  PilaArrayInt::size()  const { return n; }
int  PilaArrayInt::capacity() const { return cap; }
void PilaArrayInt::clear() { n = 0; }

void PilaArrayInt::reservar(int m) {
    if (m <= cap) return;
    int* nd = new int[m];
    for (int i = 0; i < n; ++i) nd[i] = datos[i];
    delete[] datos;
    datos = nd;
    cap = m;
}

void PilaArrayInt::push(int x) {
    if (n == cap) reservar(cap * 2);
    datos[n++] = x;
}

void PilaArrayInt::pop() {
    if (empty()) throw runtime_error("pop() en pila vacia");
    --n;
}

int& PilaArrayInt::top() {
    if (empty()) throw runtime_error("top() en pila vacia");
    return datos[n - 1];
}

const int& PilaArrayInt::top() const {
    if (empty()) throw runtime_error("top() en pila vacia");
    return datos[n - 1];
}

void PilaArrayInt::imprimir() const {
    cout << "PilaArrayInt[top->bottom]: ";
    for (int i = n - 1; i >= 0; --i) cout << datos[i] << " ";
    cout << "\n";
}
