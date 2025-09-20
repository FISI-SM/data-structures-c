#include "lista_circular.h"

int main() {
    ListaCircular lista;

    lista.insertarFinal(10);
    lista.insertarFinal(20);
    lista.insertarInicio(5);
    lista.insertarFinal(30);

    lista.imprimir();
    cout << "Tamano: " << lista.tamano() << "\n";

    auto n = lista.buscar(20);
    cout << (n ? "Encontrado 20" : "No encontrado 20") << "\n";

    lista.eliminarInicio();
    lista.imprimir();

    lista.eliminarFinal();
    lista.imprimir();

    lista.eliminarValor(10);
    lista.imprimir();

    return 0;
}
