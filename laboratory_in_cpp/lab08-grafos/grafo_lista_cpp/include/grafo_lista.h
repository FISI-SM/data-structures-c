#ifndef GRAFO_LISTA_H
#define GRAFO_LISTA_H

#include <iostream>
using namespace std;

// Nodo para lista de adyacencia
struct NodoAdj {
    int v;
    NodoAdj* sig;

    // contructor
    NodoAdj(int vv){
        v = vv;
        sig = nullptr;
    }
};

// Grafo no ponderado usando LISTA DE ADYACENCIA (array de punteros)
struct GrafoLista {
    int n;
    bool dirigido;
    NodoAdj** adj; // arreglo de tamaño n con cabezas de listas

    GrafoLista(int n_, bool dirigido_ = false) {
        n = n_;
        dirigido = dirigido_;
        adj = new NodoAdj*[n];
        for (int i = 0; i < n; ++i) {
            adj[i] = nullptr;
        }
    }

    ~GrafoLista();

    void agregarArista(int u, int v);
    void eliminarArista(int u, int v);
    bool existeArista(int u, int v) const;

    void imprimir() const;
    void bfs(int s) const;
    void dfs(int s) const;

    void liberar();

private:
    static void eliminarDeLista(NodoAdj*& head, int v);
    void dfsRec(int u, bool* vis) const;
};

#endif
