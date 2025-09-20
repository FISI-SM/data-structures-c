#include "arbol_binario_int.h"
void ArbolBinario::insertarCompleto(int v){
    Nodo* n=new Nodo(v); if(!raiz){raiz=n;return;}
    queue<Nodo*> q; q.push(raiz);
    while(!q.empty()){auto u=q.front();q.pop();
        if(!u->izq){u->izq=n;return;} else q.push(u->izq);
        if(!u->der){u->der=n;return;} else q.push(u->der);
    }
}
void ArbolBinario::preorden()const{preRec(raiz);cout<<"\n";}
void ArbolBinario::inorden()const{inRec(raiz);cout<<"\n";}
void ArbolBinario::postorden()const{postRec(raiz);cout<<"\n";}
void ArbolBinario::porNiveles()const{
    if(!raiz){cout<<"NULL\n";return;} queue<Nodo*> q; q.push(raiz);
    while(!q.empty()){auto u=q.front();q.pop(); cout<<u->dato<<" "; if(u->izq)q.push(u->izq); if(u->der)q.push(u->der);} cout<<"\n";
}
int ArbolBinario::altura()const{return altRec(raiz);}
int ArbolBinario::contarNodos()const{return cntRec(raiz);}
void ArbolBinario::reflejar(){refRec(raiz);}
void ArbolBinario::liberar(){freeRec(raiz); raiz=nullptr;}
void ArbolBinario::preRec(Nodo* n)const{ if(!n)return; cout<<n->dato<<" "; preRec(n->izq); preRec(n->der); }
void ArbolBinario::inRec(Nodo* n)const{ if(!n)return; inRec(n->izq); cout<<n->dato<<" "; inRec(n->der); }
void ArbolBinario::postRec(Nodo* n)const{ if(!n)return; postRec(n->izq); postRec(n->der); cout<<n->dato<<" "; }
int ArbolBinario::altRec(Nodo* n)const{ if(!n)return 0; int a=altRec(n->izq), b=altRec(n->der); return 1+(a>b?a:b); }
int ArbolBinario::cntRec(Nodo* n)const{ if(!n)return 0; return 1+cntRec(n->izq)+cntRec(n->der); }
void ArbolBinario::refRec(Nodo* n){ if(!n)return; auto t=n->izq; n->izq=n->der; n->der=t; refRec(n->izq); refRec(n->der); }
void ArbolBinario::freeRec(Nodo* n){ if(!n)return; freeRec(n->izq); freeRec(n->der); delete n; }
