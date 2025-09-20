#include "lista_doble_circular.h"

int main() {
    ListaDobleCircular L;

    // Inserciones
    L.insertarFinal(10);
    L.insertarFinal(20);
    L.insertarInicio(5);
    L.insertarFinal(30);

    L.imprimir();           // 5 <-> 10 <-> 20 <-> 30 <-> (doble circular)
    L.imprimirReversa();    // 30 <-> 20 <-> 10 <-> 5 <-> (doble circular, reversa)
    cout << "Tamano: " << L.tamano() << "\n";

    // Buscar
    auto p = L.buscar(20);
    cout << (p ? "Encontrado 20" : "No encontrado 20") << "\n";

    // Eliminaciones
    L.eliminarInicio();     // quita 5
    L.imprimir();

    L.eliminarFinal();      // quita 30
    L.imprimir();

    L.eliminarValor(10);    // quita 10
    L.imprimir();

    // Destructor libera memoria
    return 0;
}
