#include "grafo_lista.h"
#include <climits>
#include <iomanip>

GrafoLista::~GrafoLista() { liberar(); }

void GrafoLista::agregarArista(int u, int v, int peso) {
    if (u < 0 || v < 0 || u >= n || v >= n) 
        return;
    // insertar al inicio de la lista de u
    NodoAdj* a = new NodoAdj(v, peso);
    a->sig = adj[u]; 
    adj[u] = a;

    if (!dirigido) {
        NodoAdj* b = new NodoAdj(u, peso);
        b->sig = adj[v]; 
        adj[v] = b;
    }
}

void GrafoLista::eliminarArista(int u, int v) {
    if (u < 0 || v < 0 || u >= n || v >= n) 
        return;
    eliminarDeLista(adj[u], v);
    if (!dirigido) 
        eliminarDeLista(adj[v], u);
}

bool GrafoLista::existeArista(int u, int v) const {
    if (u < 0 || v < 0 || u >= n || v >= n) 
        return false;
    for (NodoAdj* p = adj[u]; p; p = p->sig)
        if (p->val == v) 
            return true;

    return false;
}

void GrafoLista::imprimir() const {
    cout << "Listas de adyacencia (con pesos):\n";
    for (int u = 0; u < n; ++u) {
        cout << u << ": ";
        for (NodoAdj* p = adj[u]; p; p = p->sig) {
            cout << "(" << p->val << "," << p->peso << ") -> ";
        }
        cout << "NULL\n";
    }
}

void GrafoLista::floydWarshall() const {
    // Crear matriz de distancias inicial
    int** dist = new int*[n];
    for (int i = 0; i < n; ++i) {
        dist[i] = new int[n];
        for (int j = 0; j < n; ++j) {
            if (i == j)
                dist[i][j] = 0;
            else
                dist[i][j] = INT_MAX;
        }
    }
    
    // Inicializar con las aristas existentes
    for (int u = 0; u < n; ++u) {
        for (NodoAdj* p = adj[u]; p; p = p->sig) {
            int v = p->val;
            int peso = p->peso;
            dist[u][v] = peso;
        }
    }
    
    // Algoritmo de Floyd-Warshall
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX) {
                    if (dist[i][j] > dist[i][k] + dist[k][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }
    
    // Imprimir resultados
    cout << "\nFloyd-Warshall - Matriz de distancias más cortas:\n";
    cout << "    ";
    for (int j = 0; j < n; ++j) {
        cout << setw(6) << j;
    }
    cout << "\n";
    
    for (int i = 0; i < n; ++i) {
        cout << setw(3) << i << " ";
        for (int j = 0; j < n; ++j) {
            if (dist[i][j] == INT_MAX)
                cout << setw(6) << "INF";
            else
                cout << setw(6) << dist[i][j];
        }
        cout << "\n";
    }
    
    // Liberar memoria
    for (int i = 0; i < n; ++i) {
        delete[] dist[i];
    }
    delete[] dist;
}

void GrafoLista::liberar() {
    if (!adj) 
        return;
    for (int u = 0; u < n; ++u) {
        NodoAdj* p = adj[u];
        while (p) { 
            NodoAdj* nx = p->sig; 
            delete p; 
            p = nx; 
        }
    }
    delete[] adj;
    adj = nullptr;
    n = 0;
}

// ===== privados =====
void GrafoLista::eliminarDeLista(NodoAdj*& head, int v) {
    NodoAdj* cur = head;
    NodoAdj* prev = nullptr;
    while (cur && cur->val != v) { 
        prev = cur; 
        cur = cur->sig; 
    }
    if (!cur) 
        return;
    if (!prev) 
        head = cur->sig;
    else 
        prev->sig = cur->sig;
    delete cur;
}