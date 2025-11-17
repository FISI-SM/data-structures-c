#include "grafo_lista.h"

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

// Estructura Union-Find para detectar ciclos en Kruskal
class UnionFind {
private:
    int* parent;
    int* rank;
    int n;

public:
    UnionFind(int n_) : n(n_) {
        parent = new int[n];
        rank = new int[n];
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    ~UnionFind() {
        delete[] parent;
        delete[] rank;
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]); // Path compression
        return parent[x];
    }

    bool unite(int x, int y) {
        int px = find(x);
        int py = find(y);
        if (px == py) return false; // Ya están en el mismo conjunto

        // Union by rank
        if (rank[px] < rank[py])
            parent[px] = py;
        else if (rank[px] > rank[py])
            parent[py] = px;
        else {
            parent[py] = px;
            rank[px]++;
        }
        return true;
    }
};

void GrafoLista::kruskal() const {
    if (dirigido) {
        cout << "Kruskal requiere un grafo no dirigido.\n";
        return;
    }

    // Recopilar todas las aristas del grafo
    vector<Arista> aristas;
    for (int u = 0; u < n; ++u) {
        for (NodoAdj* p = adj[u]; p; p = p->sig) {
            int v = p->val;
            // Solo agregar una vez (u < v para evitar duplicados)
            if (u < v) {
                aristas.push_back(Arista(u, v, p->peso));
            }
        }
    }

    // Ordenar aristas por peso (ascendente)
    sort(aristas.begin(), aristas.end());

    // Union-Find para detectar ciclos
    UnionFind uf(n);
    
    // Almacenar aristas del MST
    vector<Arista> mst;
    int pesoTotal = 0;

    // Aplicar algoritmo de Kruskal
    for (const Arista& a : aristas) {
        // Si agregar esta arista no forma ciclo, agregarla al MST
        if (uf.unite(a.u, a.v)) {
            mst.push_back(a);
            pesoTotal += a.peso;
        }
    }

    // Imprimir resultados
    cout << "Algoritmo de Kruskal - Arbol de Expansion Minima (MST):\n";
    if (mst.empty()) {
        cout << "  El grafo no tiene arbol de expansion minima.\n";
        return;
    }

    cout << "  Aristas del MST:\n";
    for (const Arista& a : mst) {
        cout << "    (" << a.u << ", " << a.v << ") peso: " << a.peso << "\n";
    }
    cout << "  Peso total del MST: " << pesoTotal << "\n";
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