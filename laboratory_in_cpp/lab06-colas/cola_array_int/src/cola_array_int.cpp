#include "cola_array_int.h"
#include <algorithm> // para swap

ColaArrayInt::ColaArrayInt(int capacidad_inicial) {
    if (capacidad_inicial <= 0) capacidad_inicial = 1;
    datos = new int[capacidad_inicial];
    n = 0;
    cap = capacidad_inicial;
    head = 0;
    tail = 0;
}

ColaArrayInt::ColaArrayInt(const ColaArrayInt& o) {
    datos = new int[o.cap];
    n = o.n;
    cap = o.cap;
    head = 0;
    tail = n;
    for (int i = 0; i < n; ++i) {
        datos[i] = o.datos[(o.head + i) % o.cap];
    }
}

ColaArrayInt& ColaArrayInt::operator=(ColaArrayInt o) {
    swap(datos, o.datos);
    swap(n, o.n);
    swap(cap, o.cap);
    swap(head, o.head);
    swap(tail, o.tail);
    return *this;
}

ColaArrayInt::~ColaArrayInt() {
    delete[] datos;
}

bool ColaArrayInt::empty() const { return n == 0; }
int  ColaArrayInt::size()  const { return n; }
int  ColaArrayInt::capacity() const { return cap; }

void ColaArrayInt::clear() {
    n = 0;
    head = 0;
    tail = 0;
}

void ColaArrayInt::reservar(int m) {
    if (m <= cap) return;
    int* nd = new int[m];
    for (int i = 0; i < n; ++i) {
        nd[i] = datos[(head + i) % cap];
    }
    delete[] datos;
    datos = nd;
    cap = m;
    head = 0;
    tail = n;
}

void ColaArrayInt::push(int x) {
    if (n == cap) reservar(cap * 2);
    datos[tail] = x;
    tail = (tail + 1) % cap;
    ++n;
}

void ColaArrayInt::pop() {
    if (empty()) throw runtime_error("pop() en cola vacia");
    head = (head + 1) % cap;
    --n;
}

int& ColaArrayInt::front() {
    if (empty()) throw runtime_error("front() en cola vacia");
    return datos[head];
}

const int& ColaArrayInt::front() const {
    if (empty()) throw runtime_error("front() en cola vacia");
    return datos[head];
}

int& ColaArrayInt::back() {
    if (empty()) throw runtime_error("back() en cola vacia");
    return datos[(tail + cap - 1) % cap];
}

const int& ColaArrayInt::back() const {
    if (empty()) throw runtime_error("back() en cola vacia");
    return datos[(tail + cap - 1) % cap];
}

void ColaArrayInt::imprimir() const {
    cout << "ColaArrayInt[front->back]: ";
    for (int i = 0; i < n; ++i) {
        cout << datos[(head + i) % cap] << " ";
    }
    cout << "\n";
}
