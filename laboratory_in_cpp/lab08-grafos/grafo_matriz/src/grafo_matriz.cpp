#include "grafo_matriz.h"
#include <queue>

// Constructor
GrafoMatriz::GrafoMatriz(int n_, bool dirigido_)
    : n(n_), dirigido(dirigido_) {
    adj = new int*[n];
    for (int i = 0; i < n; ++i) {
        adj[i] = new int[n];
        for (int j = 0; j < n; ++j) adj[i][j] = 0;
    }
}

// Destructor
GrafoMatriz::~GrafoMatriz() { liberar(); }

void GrafoMatriz::agregarArista(int u, int v) {
    if (u < 0 || v < 0 || u >= n || v >= n) return;
    adj[u][v] = 1;
    if (!dirigido) adj[v][u] = 1;
}

void GrafoMatriz::eliminarArista(int u, int v) {
    if (u < 0 || v < 0 || u >= n || v >= n) return;
    adj[u][v] = 0;
    if (!dirigido) adj[v][u] = 0;
}

bool GrafoMatriz::existeArista(int u, int v) const {
    if (u < 0 || v < 0 || u >= n || v >= n) return false;
    return adj[u][v] != 0;
}

void GrafoMatriz::imprimir() const {
    cout << "Matriz (" << n << "x" << n << ")\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) cout << adj[i][j] << " ";
        cout << "\n";
    }
}

void GrafoMatriz::bfs(int s) const {
    if (s < 0 || s >= n) return;
    bool* vis = new bool[n];
    for (int i = 0; i < n; ++i) vis[i] = false;
    queue<int> q;
    vis[s] = true; q.push(s);
    cout << "BFS: ";
    while (!q.empty()) {
        int u = q.front(); q.pop();
        cout << u << " ";
        for (int v = 0; v < n; ++v) {
            if (adj[u][v] && !vis[v]) {
                vis[v] = true; q.push(v);
            }
        }
    }
    cout << "\n";
    delete[] vis;
}

void GrafoMatriz::dfs(int s) const {
    if (s < 0 || s >= n) return;
    bool* vis = new bool[n];
    for (int i = 0; i < n; ++i) vis[i] = false;
    cout << "DFS: ";
    dfsRec(s, vis);
    cout << "\n";
    delete[] vis;
}

void GrafoMatriz::liberar() {
    if (!adj) return;
    for (int i = 0; i < n; ++i) {
        delete[] adj[i];
    }
    delete[] adj;
    adj = nullptr;
    n = 0;
}

// -------- privados --------
void GrafoMatriz::dfsRec(int u, bool* vis) const {
    vis[u] = true;
    cout << u << " ";
    for (int v = 0; v < n; ++v) {
        if (adj[u][v] && !vis[v]) dfsRec(v, vis);
    }
}
