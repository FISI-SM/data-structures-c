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

void GrafoLista::prim(int s) const {
    if (s < 0 || s >= n) 
        return;
    
    // Array de pesos mínimos para cada nodo
    int* pesoMin = new int[n];
    for (int i = 0; i < n; ++i)
        pesoMin[i] = INT_MAX;
    pesoMin[s] = 0;
    
    // Array de padres para construir el MST
    int* padre = new int[n];
    for (int i = 0; i < n; ++i)
        padre[i] = -1;
    
    // Cola de prioridad: (peso, vértice)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, s});
    
    // Array de visitados (nodos en el MST)
    bool* enMST = new bool[n];
    for (int i = 0; i < n; ++i)
        enMST[i] = false;
    
    int pesoTotal = 0;
    
    cout << "Algoritmo de Prim (MST) desde " << s << ":\n";
    
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        
        if (enMST[u]) continue;
        enMST[u] = true;
        pesoTotal += pesoMin[u];
        
        // Explorar aristas adyacentes
        for (NodoAdj* p = adj[u]; p; p = p->sig) {
            int v = p->val;
            int peso = p->peso;
            
            // Si v no está en el MST y el peso es menor al peso mínimo actual
            if (!enMST[v] && peso < pesoMin[v]) {
                pesoMin[v] = peso;
                padre[v] = u;
                pq.push({pesoMin[v], v});
            }
        }
    }
    
    // Imprimir resultados
    cout << "Arbol de Expansion Minima (MST):\n";
    cout << "Peso total: " << pesoTotal << "\n";
    cout << "Aristas del MST:\n";
    for (int i = 0; i < n; ++i) {
        if (padre[i] != -1) {
            cout << "  (" << padre[i] << ", " << i << ") - peso: " << pesoMin[i] << "\n";
        }
    }
    
    delete[] pesoMin;
    delete[] padre;
    delete[] enMST;
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