#include "grafo_lista.h"
#include "cola.h"

GrafoLista::~GrafoLista() { liberar(); }

void GrafoLista::agregarArista(int u, int v) {
    if (u < 0 || v < 0 || u >= n || v >= n) 
        return;
    // insertar al inicio de la lista de u
    NodoGrafo* a = new NodoGrafo(v);
    a->sig = adj[u]; 
    adj[u] = a;

    if (!dirigido) {
        NodoGrafo* b = new NodoGrafo(u);
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
    for (NodoGrafo* p = adj[u]; p; p = p->sig)
        if (p->val == v) 
            return true;

    return false;
}

void GrafoLista::imprimir() const {
    cout << "Listas de adyacencia:\n";
    for (int u = 0; u < n; ++u) {
        cout << u << ": ";
        for (NodoGrafo* p = adj[u]; p; p = p->sig) {
            cout << p->val << " -> ";
        }
        cout << "NULL\n";
    }
}

void GrafoLista::bfs(int s) const {
    if (s < 0 || s >= n) 
        return;
    bool* vis = new bool[n];
    for (int i = 0; i < n; ++i) 
        vis[i] = false;

   
    Cola Q;   
    vis[s] = true; 
    Q.push(s);

    cout << "BFS: ";
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        cout << u << " ";
        for (NodoGrafo* p = adj[u]; p; p = p->sig) {
            int v = p->val;
            if (!vis[v]) { 
                vis[v] = true; 
                Q.push(v); 
            }
        }
    }
    cout << "\n";
    delete[] vis;
}

void GrafoLista::dfs(int s) const {
    if (s < 0 || s >= n) 
        return;
    bool* vis = new bool[n];
    for (int i = 0; i < n; ++i) 
        vis[i] = false;
    cout << "DFS: ";
    dfsRec(s, vis);
    cout << "\n";
    delete[] vis;
}

void GrafoLista::liberar() {
    if (!adj) 
        return;
    for (int u = 0; u < n; ++u) {
        NodoGrafo* p = adj[u];
        while (p) { 
            NodoGrafo* nx = p->sig; 
            delete p; 
            p = nx; 
        }
    }
    delete[] adj;
    adj = nullptr;
    n = 0;
}

// ===== privados =====
void GrafoLista::eliminarDeLista(NodoGrafo*& head, int v) {
    NodoGrafo* cur = head;
    NodoGrafo* prev = nullptr;
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

void GrafoLista::dfsRec(int u, bool* vis) const {
    vis[u] = true;
    cout << u << " ";
    for (NodoGrafo* p = adj[u]; p; p = p->sig) {
        int v = p->val;
        if (!vis[v]) 
            dfsRec(v, vis);
    }
}
