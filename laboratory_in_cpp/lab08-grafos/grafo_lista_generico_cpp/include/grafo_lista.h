#ifndef GRAFO_LISTA_H
#define GRAFO_LISTA_H

#include <iostream>
#include <queue>
using namespace std;

// Nodo para lista de adyacencia
struct NodoAdj {
    int v;
    NodoAdj* sig;
    NodoAdj(int vv) : v(vv), sig(nullptr) {}
};

// Grafo no ponderado usando LISTA DE ADJACENCIA (array de punteros)
struct GrafoLista {
    int n;
    bool dirigido;
    NodoAdj** adj; // arreglo de tamaño n con cabezas de listas

    GrafoLista(int n_, bool dirigido_ = false) {
        n = n_;
        dirigido = dirigido_;
        adj = new NodoAdj*[n];
        for (int i = 0; i < n; ++i) adj[i] = nullptr;
    }

    ~GrafoLista() { liberar(); }

    void agregarArista(int u, int v) {
        if (u < 0 || v < 0 || u >= n || v >= n) return;
        // insertar al inicio de la lista de u
        NodoAdj* a = new NodoAdj(v);
        a->sig = adj[u]; adj[u] = a;
        if (!dirigido) {
            NodoAdj* b = new NodoAdj(u);
            b->sig = adj[v]; adj[v] = b;
        }
    }

    void eliminarArista(int u, int v) {
        if (u < 0 || v < 0 || u >= n || v >= n) return;
        // eliminar v de la lista de u
        eliminarDeLista(adj[u], v);
        if (!dirigido) eliminarDeLista(adj[v], u);
    }

    bool existeArista(int u, int v) const {
        if (u < 0 || v < 0 || u >= n || v >= n) return false;
        for (NodoAdj* p = adj[u]; p; p = p->sig)
            if (p->v == v) return true;
        return false;
    }

    void imprimir() const {
        cout << "Listas de adyacencia:\n";
        for (int u = 0; u < n; ++u) {
            cout << u << ": ";
            for (NodoAdj* p = adj[u]; p; p = p->sig) {
                cout << p->v << " -> ";
            }
            cout << "NULL\n";
        }
    }

    void bfs(int s) const {
        if (s < 0 || s >= n) return;
        bool* vis = new bool[n];
        for (int i = 0; i < n; ++i) vis[i] = false;
        queue<int> q;
        vis[s] = true; q.push(s);
        cout << "BFS: ";
        while (!q.empty()) {
            int u = q.front(); q.pop();
            cout << u << " ";
            for (NodoAdj* p = adj[u]; p; p = p->sig) {
                int v = p->v;
                if (!vis[v]) { vis[v] = true; q.push(v); }
            }
        }
        cout << "\n";
        delete [] vis;
    }

    void dfs(int s) const {
        if (s < 0 || s >= n) return;
        bool* vis = new bool[n];
        for (int i = 0; i < n; ++i) vis[i] = false;
        cout << "DFS: ";
        dfsRec(s, vis);
        cout << "\n";
        delete [] vis;
    }

    void liberar() {
        if (!adj) return;
        for (int u = 0; u < n; ++u) {
            NodoAdj* p = adj[u];
            while (p) { NodoAdj* nx = p->sig; delete p; p = nx; }
        }
        delete [] adj;
        adj = nullptr;
        n = 0;
    }

private:
    static void eliminarDeLista(NodoAdj*& head, int v) {
        NodoAdj* cur = head;
        NodoAdj* prev = nullptr;
        while (cur && cur->v != v) { prev = cur; cur = cur->sig; }
        if (!cur) return;
        if (!prev) head = cur->sig;
        else prev->sig = cur->sig;
        delete cur;
    }

    void dfsRec(int u, bool* vis) const {
        vis[u] = true;
        cout << u << " ";
        for (NodoAdj* p = adj[u]; p; p = p->sig) {
            int v = p->v;
            if (!vis[v]) dfsRec(v, vis);
        }
    }
};

#endif
