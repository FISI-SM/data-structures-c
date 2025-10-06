#include "lista_doble.h"

// ======================
// ADICIONAR / INSERTAR
// ======================

void ListaDoble::AdicionarAlInicioDoble(int v) {
    Nodo* n = new Nodo(v);
    if (!cabeza) { 
        cabeza = cola = n; 
        tam++; // incremento
        return; 
    }
    n->sig = cabeza;
    cabeza->ant = n;
    cabeza = n;
    tam++; // incremento
}

void ListaDoble::AdicionarDoble(int v) {
    Nodo* n = new Nodo(v);
    if (!cola) { 
        cabeza = cola = n; 
        tam++; // incremento
        return; 
    }
    n->ant = cola;
    cola->sig = n;
    cola = n;
    tam++; // incremento
}

// AdicionarEnPosicionDoble(dato, posicion)  (0-based; si pos >= tamaño, agrega al final)
void ListaDoble::AdicionarEnPosicionDoble(int v, int posicion) {
    if (posicion <= 0 || !cabeza) { 
        AdicionarAlInicioDoble(v); 
        return; 
    }

    int i = 0;
    for (Nodo* cur = cabeza; cur; cur = cur->sig, ++i) {
        if (i == posicion) {
            Nodo* n = new Nodo(v);
            n->ant = cur->ant;
            n->sig = cur;
            cur->ant->sig = n;
            cur->ant = n;
            tam++; // incremento
            return;
        }
    }

    // si posición excede tamaño -> agregar al final
    AdicionarDoble(v);
}

// AdicionarEnOrdenDoble(dato)  (inserta manteniendo orden ascendente)
void ListaDoble::AdicionarEnOrdenDoble(int v) {
    if (!cabeza || v <= cabeza->dato) { 
        AdicionarAlInicioDoble(v); 
        return; 
    }
    if (v >= cola->dato) { 
        AdicionarDoble(v); 
        return; 
    }
    Nodo* cur = cabeza->sig;
    while (cur && cur->dato < v) cur = cur->sig;

    Nodo* n = new Nodo(v);
    n->ant = cur->ant;
    n->sig = cur;
    cur->ant->sig = n;
    cur->ant = n;
    tam++; // incremento
}

// ======================
// RETIRAR / ELIMINAR
// ======================

bool ListaDoble::RetiraDelInicioDoble() {
    if (!cabeza) return false;
    Nodo* n = cabeza;
    if (cabeza == cola) { 
        cabeza = cola = nullptr; 
    } else { 
        cabeza = cabeza->sig; 
        cabeza->ant = nullptr; 
    }
    delete n;
    tam--; // decremento
    return true;
}

bool ListaDoble::RetiraDoble() {
    if (!cola) return false;
    Nodo* n = cola;
    if (cabeza == cola) { 
        cabeza = cola = nullptr; 
    } else { 
        cola = cola->ant; 
        cola->sig = nullptr; 
    }
    delete n;
    tam--; // decremento
    return true;
}

bool ListaDoble::RetiraEspecificoDoble(int v) {
    Nodo* cur = cabeza;
    while (cur && cur->dato != v) cur = cur->sig;
    if (!cur) return false;

    if (cur == cabeza) return RetiraDelInicioDoble();
    if (cur == cola)   return RetiraDoble();

    cur->ant->sig = cur->sig;
    cur->sig->ant = cur->ant;
    delete cur;
    tam--; // decremento
    return true;
}

// RetiraDeLaPosicionDoble(posicion)  (0-based)
bool ListaDoble::RetiraDeLaPosicionDoble(int posicion) {
    if (posicion < 0 || !cabeza) return false;
    int i = 0;
    for (Nodo* cur = cabeza; cur; cur = cur->sig, ++i) {
        if (i == posicion) {
            if (cur == cabeza) return RetiraDelInicioDoble();
            if (cur == cola)   return RetiraDoble();
            cur->ant->sig = cur->sig;
            cur->sig->ant = cur->ant;
            delete cur;
            tam--; // decremento
            return true;
        }
    }
    return false;
}

// ======================
// UTILITARIAS
// ======================

Nodo* ListaDoble::buscar(int v) {
    for (Nodo* cur = cabeza; cur; cur = cur->sig)
        if (cur->dato == v) return cur;
    return nullptr;
}

// Se mantiene el contador, por lo que ya no se recorre
int ListaDoble::tamano() const {
    return tam;
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
    tam = 0; // reinicia tamaño
}

// ======================
// TESTE Y VERIFICACIÓN
// ======================

bool ListaDoble::ListaVaciaDoble() const {
    return tam == 0;
}

int ListaDoble::PosicionDoble(int v) const {
    int i = 0;
    for (Nodo* cur = cabeza; cur; cur = cur->sig, ++i) {
        if (cur->dato == v) return i;
    }
    return -1;
}

bool ListaDoble::ContieneDoble(int v) const {
    return PosicionDoble(v) != -1;
}

// ======================
// INICIALIZAR O BORRAR
// ======================

void ListaDoble::CreaListaDoble() {
    liberar();
}

void ListaDoble::DestruyeListaDoble() {
    liberar();
}
