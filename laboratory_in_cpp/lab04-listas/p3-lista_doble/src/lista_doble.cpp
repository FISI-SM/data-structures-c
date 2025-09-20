#include "lista_doble.h"

void ListaDoble::insertarInicio(int v) {
    Nodo* n = new Nodo(v);
    if (!cabeza) {
        cabeza = cola = n;
        return;
    }
    n->sig = cabeza;
    cabeza->ant = n;
    cabeza = n;
}

void ListaDoble::insertarFinal(int v) {
    Nodo* n = new Nodo(v);
    if (!cola) {
        cabeza = cola = n;
        return;
    }
    n->ant = cola;
    cola->sig = n;
    cola = n;
}

bool ListaDoble::eliminarInicio() {
    if (!cabeza) return false;
    Nodo* n = cabeza;
    if (cabeza == cola) {
        cabeza = cola = nullptr;
    } else {
        cabeza = cabeza->sig;
        cabeza->ant = nullptr;
    }
    delete n;
    return true;
}

bool ListaDoble::eliminarFinal() {
    if (!cola) return false;
    Nodo* n = cola;
    if (cabeza == cola) {
        cabeza = cola = nullptr;
    } else {
        cola = cola->ant;
        cola->sig = nullptr;
    }
    delete n;
    return true;
}

bool ListaDoble::eliminarValor(int v) {
    Nodo* cur = cabeza;
    while (cur && cur->dato != v) cur = cur->sig;
    if (!cur) return false;

    if (cur == cabeza) return eliminarInicio();
    if (cur == cola)   return eliminarFinal();

    cur->ant->sig = cur->sig;
    cur->sig->ant = cur->ant;
    delete cur;
    return true;
}

Nodo* ListaDoble::buscar(int v) {
    for (Nodo* cur = cabeza; cur; cur = cur->sig)
        if (cur->dato == v) return cur;
    return nullptr;
}

int ListaDoble::tamano() const {
    int c = 0;
    for (Nodo* cur = cabeza; cur; cur = cur->sig) ++c;
    return c;
}

void ListaDoble::imprimir() const {
    cout << "Lista: ";
    for (Nodo* cur = cabeza; cur; cur = cur->sig)
        cout << cur->dato << " <-> ";
    cout << "NULL\n";
}

void ListaDoble::imprimirReversa() const {
    cout << "Reversa: ";
    for (Nodo* cur = cola; cur; cur = cur->ant)
        cout << cur->dato << " <-> ";
    cout << "NULL\n";
}

void ListaDoble::liberar() {
    Nodo* cur = cabeza;
    while (cur) {
        Nodo* nxt = cur->sig;
        delete cur;
        cur = nxt;
    }
    cabeza = cola = nullptr;
}
