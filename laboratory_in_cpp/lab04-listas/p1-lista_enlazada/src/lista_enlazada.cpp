#include "lista_enlazada.h"

// Insertar al inicio
void Lista::insertarInicio(int valor) {
    Nodo* nuevo = new Nodo(valor);
    nuevo->sig = cabeza;
    cabeza = nuevo;
}

// Insertar al final
void Lista::insertarFinal(int valor) {
    Nodo* nuevo = new Nodo(valor);
    if (!cabeza) {
        cabeza = nuevo;
        return;
    }
    Nodo* temp = cabeza;
    while (temp->sig) temp = temp->sig;
    temp->sig = nuevo;
}

// Eliminar primera ocurrencia
void Lista::eliminar(int valor) {
    Nodo* temp = cabeza;
    Nodo* anterior = nullptr;

    while (temp && temp->dato != valor) {
        anterior = temp;
        temp = temp->sig;
    }

    if (!temp) return; // no encontrado

    if (!anterior) {
        cabeza = temp->sig;
    } else {
        anterior->sig = temp->sig;
    }
    delete temp;
}

// Buscar un valor
Nodo* Lista::buscar(int valor) {
    Nodo* temp = cabeza;
    while (temp) {
        if (temp->dato == valor) return temp;
        temp = temp->sig;
    }
    return nullptr;
}

// Imprimir la lista
void Lista::imprimir() {
    Nodo* temp = cabeza;
    cout << "Lista: ";
    while (temp) {
        cout << temp->dato << " -> ";
        temp = temp->sig;
    }
    cout << "NULL\n";
}

// Liberar memoria
void Lista::liberar() {
    Nodo* temp = cabeza;
    while (temp) {
        Nodo* siguiente = temp->sig;
        delete temp;
        temp = siguiente;
    }
    cabeza = nullptr;
}
