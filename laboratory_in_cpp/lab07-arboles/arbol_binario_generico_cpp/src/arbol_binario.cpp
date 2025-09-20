#include "arbol_binario.h"

void ArbolBinario::insertarCompleto(int v) {
    Nodo* nuevo = new Nodo(v);
    if (!raiz) { raiz = nuevo; return; }

    queue<Nodo*> q;
    q.push(raiz);
    while (!q.empty()) {
        Nodo* cur = q.front(); q.pop();
        if (!cur->izq) { cur->izq = nuevo; return; }
        else q.push(cur->izq);
        if (!cur->der) { cur->der = nuevo; return; }
        else q.push(cur->der);
    }
}

void ArbolBinario::preorden() const {
    preordenRec(raiz);
    cout << "\n";
}
void ArbolBinario::inorden() const {
    inordenRec(raiz);
    cout << "\n";
}
void ArbolBinario::postorden() const {
    postordenRec(raiz);
    cout << "\n";
}

void ArbolBinario::porNiveles() const {
    if (!raiz) { cout << "NULL\n"; return; }
    queue<Nodo*> q;
    q.push(raiz);
    while (!q.empty()) {
        Nodo* cur = q.front(); q.pop();
        cout << cur->dato << " ";
        if (cur->izq) q.push(cur->izq);
        if (cur->der) q.push(cur->der);
    }
    cout << "\n";
}

int ArbolBinario::altura() const {
    return alturaRec(raiz);
}

int ArbolBinario::contarNodos() const {
    return contarRec(raiz);
}

void ArbolBinario::reflejar() {
    reflejarRec(raiz);
}

void ArbolBinario::liberar() {
    liberarRec(raiz);
    raiz = nullptr;
}

// ---- privados ----
void ArbolBinario::preordenRec(Nodo* n) const {
    if (!n) return;
    cout << n->dato << " ";
    preordenRec(n->izq);
    preordenRec(n->der);
}
void ArbolBinario::inordenRec(Nodo* n) const {
    if (!n) return;
    inordenRec(n->izq);
    cout << n->dato << " ";
    inordenRec(n->der);
}
void ArbolBinario::postordenRec(Nodo* n) const {
    if (!n) return;
    postordenRec(n->izq);
    postordenRec(n->der);
    cout << n->dato << " ";
}

int ArbolBinario::alturaRec(Nodo* n) const {
    if (!n) return 0;
    int hi = alturaRec(n->izq);
    int hd = alturaRec(n->der);
    return 1 + max(hi, hd);
}

int ArbolBinario::contarRec(Nodo* n) const {
    if (!n) return 0;
    return 1 + contarRec(n->izq) + contarRec(n->der);
}

void ArbolBinario::reflejarRec(Nodo* n) {
    if (!n) return;
    swap(n->izq, n->der);
    reflejarRec(n->izq);
    reflejarRec(n->der);
}

void ArbolBinario::liberarRec(Nodo* n) {
    if (!n) return;
    liberarRec(n->izq);
    liberarRec(n->der);
    delete n;
}
