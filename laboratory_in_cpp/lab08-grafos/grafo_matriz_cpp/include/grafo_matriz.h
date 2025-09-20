#ifndef GRAFO_MATRIZ_H
#define GRAFO_MATRIZ_H

#include <iostream>
using namespace std;

// Grafo no ponderado usando MATRIZ de adyacencia (new[])
struct GrafoMatriz {
    int   n;         // número de vértices [0..n-1]
    bool  dirigido;  // true = dirigido, false = no dirigido
    int** adj;       // matriz n x n con 0/1

    // Constructor / Destructor
    GrafoMatriz(int n_, bool dirigido_ = false);
    ~GrafoMatriz();

    // Operaciones sobre aristas
    void agregarArista(int u, int v);
    void eliminarArista(int u, int v);
    bool existeArista(int u, int v) const;

    // Utilidades
    void imprimir() const;
    void bfs(int s) const;
    void dfs(int s) const;

    void liberar();

private:
    void dfsRec(int u, bool* vis) const;
};

#endif
