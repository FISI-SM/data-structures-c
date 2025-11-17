#include "grafo_lista.h"
#include <queue>

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

void GrafoLista::dijkstra(int s) const {
    if (s < 0 || s >= n) 
        return;
    
    // Array de distancias
    int* dist = new int[n];
    for (int i = 0; i < n; ++i)
        dist[i] = INT_MAX;
    dist[s] = 0;
    
    // Cola de prioridad: (distancia, vértice)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, s});
    
    // Array de visitados
    bool* vis = new bool[n];
    for (int i = 0; i < n; ++i)
        vis[i] = false;
    
    cout << "Dijkstra desde " << s << ":\n";
    
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        
        if (vis[u]) continue;
        vis[u] = true;
        
        // Relajar aristas adyacentes
        for (NodoAdj* p = adj[u]; p; p = p->sig) {
            int v = p->val;
            int peso = p->peso;
            
            if (!vis[v] && dist[u] != INT_MAX && dist[u] + peso < dist[v]) {
                dist[v] = dist[u] + peso;
                pq.push({dist[v], v});
            }
        }
    }
    
    // Imprimir resultados
    cout << "Distancias desde " << s << ":\n";
    for (int i = 0; i < n; ++i) {
        if (dist[i] == INT_MAX)
            cout << "  " << i << ": INF\n";
        else
            cout << "  " << i << ": " << dist[i] << "\n";
    }
    
    delete[] dist;
    delete[] vis;
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