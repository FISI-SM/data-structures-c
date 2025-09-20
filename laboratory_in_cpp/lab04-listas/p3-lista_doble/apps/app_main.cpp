#include "lista_doble.h"

int main() {
    ListaDoble L;

    L.insertarInicio(10);
    L.insertarInicio(5);
    L.insertarFinal(20);
    L.insertarFinal(30);

    L.imprimir();
    L.imprimirReversa();
    cout << "Tamano: " << L.tamano() << "\n";

    auto p = L.buscar(20);
    cout << (p ? "Encontrado 20" : "No encontrado 20") << "\n";

    L.eliminarInicio();
    L.eliminarFinal();
    L.imprimir();

    L.eliminarValor(10);
    L.imprimir();

    return 0;
}
