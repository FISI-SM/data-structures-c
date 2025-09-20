#include "lista_circular.h"

// Insertar al inicio (después de 'ultimo' pero antes del primero actual)
void ListaCircular::insertarInicio(int valor) {
    Nodo* nuevo = new Nodo(valor);

    if (ultimo == nullptr) {
        ultimo = nuevo;
        nuevo->sig = nuevo;
        return;
    }

    nuevo->sig   = ultimo->sig;
    ultimo->sig  = nuevo;
}

// Insertar al final (el nuevo se vuelve 'ultimo')
void ListaCircular::insertarFinal(int valor) {
    Nodo* nuevo = new Nodo(valor);

    if (ultimo == nullptr) {
        ultimo = nuevo;
        nuevo->sig = nuevo;
        return;
    }

    nuevo->sig   = ultimo->sig;
    ultimo->sig  = nuevo;
    ultimo       = nuevo;
}

// Eliminar primero lógico (ultimo->sig)
bool ListaCircular::eliminarInicio() {
    if (ultimo == nullptr) return false;

    Nodo* primero = ultimo->sig;
    if (primero == ultimo) {
        delete primero;
        ultimo = nullptr;
        return true;
    }

    ultimo->sig = primero->sig;
    delete primero;
    return true;
}

// Eliminar último lógico (el apuntado por 'ultimo')
bool ListaCircular::eliminarFinal() {
    if (ultimo == nullptr) return false;

    Nodo* fin = ultimo;
    if (fin->sig == fin) {
        delete fin;
        ultimo = nullptr;
        return true;
    }

    Nodo* actual = fin->sig;
    while (actual->sig != fin) {
        actual = actual->sig;
    }

    actual->sig = fin->sig;
    delete fin;
    ultimo = actual;
    return true;
}

// Eliminar primera ocurrencia de 'v'
bool ListaCircular::eliminarValor(int v) {
    if (ultimo == nullptr) return false;

    Nodo* actual = ultimo->sig;
    Nodo* prev   = ultimo;

    do {
        if (actual->dato == v) {
            if (actual == ultimo && actual->sig == actual) {
                delete actual;
                ultimo = nullptr;
                return true;
            }
            prev->sig = actual->sig;
            if (actual == ultimo) {
                ultimo = prev;
            }
            delete actual;
            return true;
        }
        prev   = actual;
        actual = actual->sig;
    } while (prev != ultimo);

    return false;
}

Nodo* ListaCircular::buscar(int valor) {
    if (ultimo == nullptr) return nullptr;

    Nodo* actual = ultimo->sig;
    do {
        if (actual->dato == valor) return actual;
        actual = actual->sig;
    } while (actual != ultimo->sig);

    return nullptr;
}

int ListaCircular::tamano() const {
    if (ultimo == nullptr) return 0;

    int count = 0;
    const Nodo* actual = ultimo->sig;
    do {
        ++count;
        actual = actual->sig;
    } while (actual != ultimo->sig);
    return count;
}

void ListaCircular::imprimir() const {
    if (ultimo == nullptr) {
        cout << "NULL\n";
        return;
    }

    const Nodo* inicio = ultimo->sig;
    const Nodo* actual = inicio;
    do {
        cout << actual->dato << " -> ";
        actual = actual->sig;
    } while (actual != inicio);
    cout << "(circular)\n";
}

void ListaCircular::liberar() {
    if (ultimo == nullptr) return;

    Nodo* inicio = ultimo->sig;
    Nodo* actual = inicio;
    while (actual != ultimo) {
        Nodo* aux = actual;
        actual = actual->sig;
        delete aux;
    }
    delete ultimo;
    ultimo = nullptr;
}
