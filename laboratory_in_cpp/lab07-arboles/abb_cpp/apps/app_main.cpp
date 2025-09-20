#include "abb.h"

int main() {
    ABB T;

    // Insertar
    for (int v : {50, 30, 70, 20, 40, 60, 80}) T.insertar(v);

    // Recorridos
    cout << "Inorden (ordenado): "; T.inorden();
    cout << "Preorden: ";           T.preorden();
    cout << "Postorden: ";          T.postorden();
    cout << "Por niveles: ";        T.porNiveles();

    // Consultas
    cout << "Min: " << T.minimo() << ", Max: " << T.maximo() << "\n";
    cout << "Contiene 60? " << (T.contiene(60) ? "si" : "no") << "\n";
    cout << "Altura: " << T.altura() << "\n";

    // Eliminar
    cout << "Eliminar 70...\n";
    T.eliminar(70);
    cout << "Inorden: "; T.inorden();
    cout << "Por niveles: "; T.porNiveles();

    T.liberar();
    cout << "Arbol liberado. Por niveles: "; T.porNiveles();
    return 0;
}
