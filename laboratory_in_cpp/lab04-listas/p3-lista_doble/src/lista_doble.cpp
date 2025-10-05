#include "lista_doble.h"

// ======================
// ADICIONAR / INSERTAR
// ======================

// AdicionarAlInicioDoble(dato)  ← antes: insertarInicio
void ListaDoble::AdicionarAlInicioDoble(int v) {
    Nodo* n = new Nodo(v);
    if (!cabeza) { cabeza = cola = n; return; }
    n->sig = cabeza;
    cabeza->ant = n;
    cabeza = n;
}

// AdicionarDoble(dato)  ← (genérico: al final) antes: insertarFinal
void ListaDoble::AdicionarDoble(int v) {
    Nodo* n = new Nodo(v);
    if (!cola) { cabeza = cola = n; return; }
    n->ant = cola;
    cola->sig = n;
    cola = n;
}

// AdicionarEnPosicionDoble(dato, posicion)  (0-based; si pos >= tamaño, agrega al final)
void ListaDoble::AdicionarEnPosicionDoble(int v, int posicion) {
    if (posicion <= 0 || !cabeza) { AdicionarAlInicioDoble(v); return; }
    int i = 0;
    for (Nodo* cur = cabeza; cur; cur = cur->sig, ++i) {
        if (i == posicion) {
            Nodo* n = new Nodo(v);
            n->ant = cur->ant;
            n->sig = cur;
            cur->ant->sig = n;
            cur->ant = n;
            return;
        }
        if (!cur->sig) { // llegó al final antes de alcanzar la posición
            AdicionarDoble(v);
            return;
        }
    }
}

// AdicionarEnOrdenDoble(dato)  (inserta manteniendo orden ascendente)
void ListaDoble::AdicionarEnOrdenDoble(int v) {
    if (!cabeza || v <= cabeza->dato) { AdicionarAlInicioDoble(v); return; }
    if (v >= cola->dato) { AdicionarDoble(v); return; }
    Nodo* cur = cabeza->sig;
    while (cur && cur->dato < v) cur = cur->sig;
    // insertar antes de cur
    Nodo* n = new Nodo(v);
    n->ant = cur->ant;
    n->sig = cur;
    cur->ant->sig = n;
    cur->ant = n;
}

// ======================
// RETIRAR / ELIMINAR
// ======================

// RetiraDoInicioDuplo()  ← antes: eliminarInicio
bool ListaDoble::RetiraDoInicioDuplo() {
    if (!cabeza) return false;
    Nodo* n = cabeza;
    if (cabeza == cola) { cabeza = cola = nullptr; }
    else { cabeza = cabeza->sig; cabeza->ant = nullptr; }
    delete n;
    return true;
}

// RetiraDoble()  (genérico: del final) ← antes: eliminarFinal
bool ListaDoble::RetiraDoble() {
    if (!cola) return false;
    Nodo* n = cola;
    if (cabeza == cola) { cabeza = cola = nullptr; }
    else { cola = cola->ant; cola->sig = nullptr; }
    delete n;
    return true;
}

// RetiraEspecificoDoble(dato)  ← antes: eliminarValor
bool ListaDoble::RetiraEspecificoDoble(int v) {
    Nodo* cur = cabeza;
    while (cur && cur->dato != v) cur = cur->sig;
    if (!cur) return false;

    if (cur == cabeza) return RetiraDoInicioDuplo();
    if (cur == cola)   return RetiraDoble();

    cur->ant->sig = cur->sig;
    cur->sig->ant = cur->ant;
    delete cur;
    return true;
}

// RetiraDeLaPosicionDoble(posicion)  (0-based)
bool ListaDoble::RetiraDeLaPosicionDoble(int posicion) {
    if (posicion < 0 || !cabeza) return false;
    int i = 0;
    for (Nodo* cur = cabeza; cur; cur = cur->sig, ++i) {
        if (i == posicion) {
            if (cur == cabeza) return RetiraDoInicioDuplo();
            if (cur == cola)   return RetiraDoble();
            cur->ant->sig = cur->sig;
            cur->sig->ant = cur->ant;
            delete cur;
            return true;
        }
    }
    return false;
}

// ======================
// UTILITARIAS (sin cambio de nombre)
// ======================

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
