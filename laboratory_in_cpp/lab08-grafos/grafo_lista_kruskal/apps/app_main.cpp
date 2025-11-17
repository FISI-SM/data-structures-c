#include "grafo_lista.h"

int main() {
    GrafoLista G(6, false); // no dirigido
    G.agregarArista(0,1,4);
    G.agregarArista(0,2,2);
    G.agregarArista(1,3,5);
    G.agregarArista(2,3,8);
    G.agregarArista(3,4,3);
    G.agregarArista(4,5,1);

    G.imprimir();
    G.kruskal();

    G.eliminarArista(3,4);
    G.imprimir();
    G.kruskal();
    return 0;
}