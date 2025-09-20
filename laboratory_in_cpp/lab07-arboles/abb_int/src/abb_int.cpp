#include "abb_int.h"
#include <stdexcept>
void ABB::insertar(int v){ raiz=insRec(raiz,v); }
bool ABB::contiene(int v) const { return contRec(raiz,v); }
bool ABB::eliminar(int v){ bool b=false; raiz=delRec(raiz,v,b); return b; }
int ABB::minimo() const { if(!raiz) throw runtime_error("vacio"); return minNode(raiz)->dato; }
int ABB::maximo() const { if(!raiz) throw runtime_error("vacio"); auto n=raiz; while(n->der) n=n->der; return n->dato; }
int ABB::altura() const { return altRec(raiz); }
void ABB::inorden() const { inRec(raiz); cout<<"\n"; }
void ABB::preorden() const { preRec(raiz); cout<<"\n"; }
void ABB::postorden() const { postRec(raiz); cout<<"\n"; }
void ABB::porNiveles() const { if(!raiz){cout<<"NULL\n";return;} queue<NodoABB*> q; q.push(raiz); while(!q.empty()){auto u=q.front();q.pop(); cout<<u->dato<<" "; if(u->izq) q.push(u->izq); if(u->der) q.push(u->der);} cout<<"\n"; }
void ABB::liberar(){ freeRec(raiz); raiz=nullptr; }
NodoABB* ABB::insRec(NodoABB* n,int v){ if(!n) return new NodoABB(v); if(v<n->dato) n->izq=insRec(n->izq,v); else if(v>n->dato) n->der=insRec(n->der,v); return n; }
bool ABB::contRec(NodoABB* n,int v) const { if(!n) return false; if(v==n->dato) return true; return v<n->dato? contRec(n->izq,v):contRec(n->der,v); }
NodoABB* ABB::delRec(NodoABB* n,int v,bool& b){ if(!n) return nullptr; if(v<n->dato) n->izq=delRec(n->izq,v,b); else if(v>n->dato) n->der=delRec(n->der,v,b); else { b=true; if(!n->izq){auto r=n->der; delete n; return r;} if(!n->der){auto l=n->izq; delete n; return l;} auto m=minNode(n->der); n->dato=m->dato; n->der=delRec(n->der,m->dato,b);} return n; }
NodoABB* ABB::minNode(NodoABB* n) const { while(n&&n->izq) n=n->izq; return n; }
int ABB::altRec(NodoABB* n) const { if(!n) return 0; int a=altRec(n->izq), b=altRec(n->der); return 1+(a>b?a:b); }
void ABB::inRec(NodoABB* n) const { if(!n) return; inRec(n->izq); cout<<n->dato<<" "; inRec(n->der); }
void ABB::preRec(NodoABB* n) const { if(!n) return; cout<<n->dato<<" "; preRec(n->izq); preRec(n->der); }
void ABB::postRec(NodoABB* n) const { if(!n) return; postRec(n->izq); postRec(n->der); cout<<n->dato<<" "; }
void ABB::freeRec(NodoABB* n){ if(!n) return; freeRec(n->izq); freeRec(n->der); delete n; }
