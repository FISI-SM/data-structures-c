#include "abb.h"
#include <stdexcept>

void ABB::insertar(int v) { raiz = insertarRec(raiz, v); }

bool ABB::contiene(int v) const { return contieneRec(raiz, v); }

bool ABB::eliminar(int v) {
    bool borrado = false;
    raiz = eliminarRec(raiz, v, borrado);
    return borrado;
}

int ABB::minimo() const {
    if (!raiz) throw runtime_error("ABB vacio");
    return minNode(raiz)->dato;
}

int ABB::maximo() const {
    if (!raiz) throw runtime_error("ABB vacio");
    NodoABB* cur = raiz;
    while (cur->der) cur = cur->der;
    return cur->dato;
}

void ABB::inorden() const { inordenRec(raiz); cout << "\n"; }
void ABB::preorden() const { preordenRec(raiz); cout << "\n"; }
void ABB::postorden() const { postordenRec(raiz); cout << "\n"; }

void ABB::porNiveles() const {
    if (!raiz) { cout << "NULL\n"; return; }
    queue<NodoABB*> q;
    q.push(raiz);
    while (!q.empty()) {
        auto cur = q.front(); q.pop();
        cout << cur->dato << " ";
        if (cur->izq) q.push(cur->izq);
        if (cur->der) q.push(cur->der);
    }
    cout << "\n";
}

int ABB::altura() const { return alturaRec(raiz); }

void ABB::liberar() { liberarRec(raiz); raiz = nullptr; }

// ---- privados ----
NodoABB* ABB::insertarRec(NodoABB* n, int v) {
    if (!n) return new NodoABB(v);
    if (v < n->dato) n->izq = insertarRec(n->izq, v);
    else if (v > n->dato) n->der = insertarRec(n->der, v);
    // si v == n->dato, ignorar o manejar duplicados (aquí los ignoramos)
    return n;
}

bool ABB::contieneRec(NodoABB* n, int v) const {
    if (!n) return false;
    if (v == n->dato) return true;
    if (v < n->dato) return contieneRec(n->izq, v);
    return contieneRec(n->der, v);
}

NodoABB* ABB::eliminarRec(NodoABB* n, int v, bool& borrado) {
    if (!n) return nullptr;
    if (v < n->dato) n->izq = eliminarRec(n->izq, v, borrado);
    else if (v > n->dato) n->der = eliminarRec(n->der, v, borrado);
    else {
        borrado = true;
        // Caso 1: 0 o 1 hijo
        if (!n->izq) { auto r = n->der; delete n; return r; }
        if (!n->der) { auto l = n->izq; delete n; return l; }
        // Caso 2: 2 hijos -> usar sucesor (mínimo del subárbol derecho)
        NodoABB* m = minNode(n->der);
        n->dato = m->dato;
        n->der = eliminarRec(n->der, m->dato, borrado /*se pondrá true igual*/);
    }
    return n;
}

NodoABB* ABB::minNode(NodoABB* n) const {
    while (n && n->izq) n = n->izq;
    return n;
}

int ABB::alturaRec(NodoABB* n) const {
    if (!n) return 0;
    int hi = alturaRec(n->izq);
    int hd = alturaRec(n->der);
    return 1 + max(hi, hd);
}

void ABB::inordenRec(NodoABB* n) const {
    if (!n) return;
    inordenRec(n->izq);
    cout << n->dato << " ";
    inordenRec(n->der);
}
void ABB::preordenRec(NodoABB* n) const {
    if (!n) return;
    cout << n->dato << " ";
    preordenRec(n->izq);
    preordenRec(n->der);
}
void ABB::postordenRec(NodoABB* n) const {
    if (!n) return;
    postordenRec(n->izq);
    postordenRec(n->der);
    cout << n->dato << " ";
}

void ABB::liberarRec(NodoABB* n) {
    if (!n) return;
    liberarRec(n->izq);
    liberarRec(n->der);
    delete n;
}
