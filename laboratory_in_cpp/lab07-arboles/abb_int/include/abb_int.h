#ifndef ABB_INT_H
#define ABB_INT_H
#include <iostream>
#include <queue>
using namespace std;
struct NodoABB{ int dato; NodoABB* izq; NodoABB* der; NodoABB(int v):dato(v),izq(nullptr),der(nullptr){} };
struct ABB{
    NodoABB* raiz; ABB():raiz(nullptr){}
    void insertar(int v); bool contiene(int v) const; bool eliminar(int v);
    int minimo() const; int maximo() const; int altura() const;
    void inorden() const; void preorden() const; void postorden() const; void porNiveles() const;
    void liberar();
private:
    NodoABB* insRec(NodoABB*,int); bool contRec(NodoABB*,int) const;
    NodoABB* delRec(NodoABB*,int,bool&); NodoABB* minNode(NodoABB*) const;
    int altRec(NodoABB*) const; void inRec(NodoABB*) const; void preRec(NodoABB*) const; void postRec(NodoABB*) const;
    void freeRec(NodoABB*);
};
#endif
