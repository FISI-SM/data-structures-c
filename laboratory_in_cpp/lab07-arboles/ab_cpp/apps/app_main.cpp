#include "arbol_binario.h"

int main() {
    ArbolBinario A;

    // Insertar como "árbol completo" (por niveles).
    for (int v : {10, 20, 30, 40, 50, 60, 70}) {
        A.insertarCompleto(v);
    }

    cout << "Preorden: ";   
    A.preorden();
    cout << "Inorden: ";    
    A.inorden();
    cout << "Postorden: ";  
    A.postorden();
    cout << "Por niveles: ";
    A.porNiveles();

    cout << "Altura: " << A.altura() << "\n";
    cout << "Nodos: "  << A.contarNodos() << "\n";

    cout << "Reflejar...\n";
    A.reflejar();
    cout << "Inorden (reflejado): "; A.inorden();

    A.liberar();
    cout << "Arbol liberado. Por niveles: "; A.porNiveles();

    return 0;
}
