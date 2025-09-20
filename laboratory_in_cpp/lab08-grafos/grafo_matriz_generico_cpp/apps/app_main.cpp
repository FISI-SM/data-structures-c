#include "grafo_matriz.h"

int main() {
    GrafoMatriz G(6, false); // no dirigido
    G.agregarArista(0,1);
    G.agregarArista(0,2);
    G.agregarArista(1,3);
    G.agregarArista(2,3);
    G.agregarArista(3,4);
    G.agregarArista(4,5);

    G.imprimir();
    G.bfs(0);
    G.dfs(0);

    G.eliminarArista(3,4);
    G.imprimir();
    return 0;
}
