#include "lista_enlazada.h"

int main() {
    Lista lista;

    lista.insertarInicio(10);
    lista.insertarInicio(20);
    lista.insertarFinal(30);
    lista.insertarFinal(40);

    lista.imprimir();

    lista.eliminar(20);
    lista.imprimir();

    Nodo* encontrado = lista.buscar(30);
    if (encontrado)
        cout << "Encontrado: " << encontrado->dato << endl;
    else
        cout << "No encontrado\n";

    return 0;
}
