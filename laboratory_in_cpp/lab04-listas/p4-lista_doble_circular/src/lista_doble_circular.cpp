#include "lista_doble_circular.h"

void ListaDobleCircular::insertarInicio(int v) {
    Nodo* n = new Nodo(v);
    if (ultimo == nullptr) {
        // primer nodo: se apunta a si mismo en ambas direcciones
        n->sig = n;
        n->ant = n;
        ultimo = n;
        return;
    }
    Nodo* primero = ultimo->sig;
    n->sig = primero;
    n->ant = ultimo;
    primero->ant = n;
    ultimo->sig = n; // n es el nuevo primero logico; 'ultimo' no cambia
}

void ListaDobleCircular::insertarFinal(int v) {
    Nodo* n = new Nodo(v);
    if (ultimo == nullptr) {
        n->sig = n;
        n->ant = n;
        ultimo = n;
        return;
    }
    Nodo* primero = ultimo->sig;
    n->sig = primero;
    n->ant = ultimo;
    primero->ant = n;
    ultimo->sig = n;
    ultimo = n; // ahora n es el ultimo
}

bool ListaDobleCircular::eliminarInicio() {
    if (ultimo == nullptr) return false;
    Nodo* primero = ultimo->sig;
    if (primero == ultimo) {
        delete primero;
        ultimo = nullptr;
        return true;
    }
    Nodo* nuevoPrimero = primero->sig;
    ultimo->sig = nuevoPrimero;
    nuevoPrimero->ant = ultimo;
    delete primero;
    return true;
}

bool ListaDobleCircular::eliminarFinal() {
    if (ultimo == nullptr) return false;
    Nodo* fin = ultimo;
    if (fin->sig == fin) { // unico nodo
        delete fin;
        ultimo = nullptr;
        return true;
    }
    Nodo* nuevoUltimo = fin->ant;
    nuevoUltimo->sig = fin->sig;      // apunta al primero
    fin->sig->ant = nuevoUltimo;      // el primero apunta hacia atras al nuevo ultimo
    delete fin;
    ultimo = nuevoUltimo;
    return true;
}

bool ListaDobleCircular::eliminarValor(int v) {
    if (ultimo == nullptr) return false;

    Nodo* cur = ultimo->sig; // primero
    do {
        if (cur->dato == v) {
            if (cur->sig == cur) { // unico nodo
                delete cur;
                ultimo = nullptr;
                return true;
            }
            cur->ant->sig = cur->sig;
            cur->sig->ant = cur->ant;
            if (cur == ultimo) {
                ultimo = cur->ant; // si borre el ultimo, retrocedo
            }
            delete cur;
            return true;
        }
        cur = cur->sig;
    } while (cur != ultimo->sig);

    return false; // no encontrado
}

Nodo* ListaDobleCircular::buscar(int v) {
    if (ultimo == nullptr) return nullptr;
    Nodo* cur = ultimo->sig; // primero
    do {
        if (cur->dato == v) return cur;
        cur = cur->sig;
    } while (cur != ultimo->sig);
    return nullptr;
}

int ListaDobleCircular::tamano() const {
    if (ultimo == nullptr) return 0;
    int c = 0;
    const Nodo* cur = ultimo->sig; // primero
    do {
        ++c;
        cur = cur->sig;
    } while (cur != ultimo->sig);
    return c;
}

void ListaDobleCircular::imprimir() const {
    if (ultimo == nullptr) {
        cout << "NULL\n";
        return;
    }
    const Nodo* inicio = ultimo->sig;
    const Nodo* cur = inicio;
    do {
        cout << cur->dato << " <-> ";
        cur = cur->sig;
    } while (cur != inicio);
    cout << "(doble circular)\n";
}

void ListaDobleCircular::imprimirReversa() const {
    if (ultimo == nullptr) {
        cout << "NULL\n";
        return;
    }
    const Nodo* fin = ultimo;
    const Nodo* cur = fin;
    do {
        cout << cur->dato << " <-> ";
        cur = cur->ant;
    } while (cur != fin);
    cout << "(doble circular, reversa)\n";
}

void ListaDobleCircular::liberar() {
    if (ultimo == nullptr) return;
    Nodo* inicio = ultimo->sig;
    Nodo* cur = inicio;
    while (cur != ultimo) {
        Nodo* nxt = cur->sig;
        delete cur;
        cur = nxt;
    }
    delete ultimo;
    ultimo = nullptr;
}
