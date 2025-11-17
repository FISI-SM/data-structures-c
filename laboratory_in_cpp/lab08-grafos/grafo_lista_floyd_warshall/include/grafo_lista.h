#ifndef GRAFO_LISTA_H
#define GRAFO_LISTA_H

#include <iostream>
using namespace std;

// Nodo para lista de adyacencia (con peso para Floyd-Warshall)
struct NodoAdj {
    int val;
    int peso;
    NodoAdj* sig;

    // constructor
    NodoAdj(int vv, int pp = 1){
        val = vv;
        peso = pp;
        sig = nullptr;
    }
};

// Grafo ponderado usando LISTA DE ADYACENCIA (array de punteros) para Floyd-Warshall
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

    void agregarArista(int u, int v, int peso = 1);
    void eliminarArista(int u, int v);
    bool existeArista(int u, int v) const;

    void imprimir() const;
    void floydWarshall() const;

    void liberar();

private:
    static void eliminarDeLista(NodoAdj*& head, int v);
};

#endif