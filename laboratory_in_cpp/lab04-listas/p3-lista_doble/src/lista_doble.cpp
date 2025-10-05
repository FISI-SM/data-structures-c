#include "lista_doble.h"

// ======================
// ADICIONAR / INSERTAR
// ======================

void ListaDoble::AdicionarAlInicioDoble(int v) {
    Nodo* n = new Nodo(v);
    if (!cabeza) { cabeza = cola = n; return; }
    n->sig = cabeza;
    cabeza->ant = n;
    cabeza = n;
}

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
        Nodo* n = new Nodo(v);
    n->ant = cur->ant;
    n->sig = cur;
    cur->ant->sig = n;
    cur->ant = n;
}

// ======================
// RETIRAR / ELIMINAR
// ======================

bool ListaDoble::RetiraDoInicioDuplo() {
    if (!cabeza) return false;
    Nodo* n = cabeza;
    if (cabeza == cola) { cabeza = cola = nullptr; }
    else { cabeza = cabeza->sig; cabeza->ant = nullptr; }
    delete n;
    return true;
}

bool ListaDoble::RetiraDoble() {
    if (!cola) return false;
    Nodo* n = cola;
    if (cabeza == cola) { cabeza = cola = nullptr; }
    else { cola = cola->ant; cola->sig = nullptr; }
    delete n;
    return true;
}

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


// ======================
// TESTE Y VERIFICACIÓN
// ======================

// ListaVaciaDoble()
bool ListaDoble::ListaVaciaDoble() const {
    return cabeza == nullptr;
}

// PosiciónDoble(dato)
// Devuelve la posición (0-based) del primer elemento con el valor dado, o -1 si no existe
int ListaDoble::PosicionDoble(int v) const {
    int i = 0;
    for (Nodo* cur = cabeza; cur; cur = cur->sig, ++i) {
        if (cur->dato == v) return i;
    }
    return -1;
}

// ContieneDoble(dato)
// Devuelve true si el dato está en la lista
bool ListaDoble::ContieneDoble(int v) const {
    return PosicionDoble(v) != -1;
}

// ======================
// INICIALIZAR O BORRAR
// ======================

// CreaListaDoble()
// Inicializa una lista vacía (equivalente a limpiar)
void ListaDoble::CreaListaDoble() {
    liberar();
}

// DestruyeListaDoble()
// Libera toda la memoria y deja la lista vacía
void ListaDoble::DestruyeListaDoble() {
    liberar();
}

