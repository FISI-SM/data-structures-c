#include "hash_int.h"
HashTableInt::HashTableInt(int capacidad){ if(capacidad<=0) capacidad=8; cap=capacidad; n=0; tabla=new NodoHash*[cap]; for(int i=0;i<cap;++i) tabla[i]=nullptr; }
HashTableInt::~HashTableInt(){ clear(); delete[] tabla; }
void HashTableInt::insertar(int k,int v){ int h=hash(k); for(NodoHash*cur=tabla[h];cur;cur=cur->sig){ if(cur->key==k){cur->value=v;return;} } NodoHash*nuevo=new NodoHash(k,v); nuevo->sig=tabla[h]; tabla[h]=nuevo; ++n; }
bool HashTableInt::contiene(int k)const{ int h=hash(k); for(NodoHash*cur=tabla[h];cur;cur=cur->sig) if(cur->key==k) return true; return false; }
bool HashTableInt::eliminar(int k){ int h=hash(k); NodoHash*cur=tabla[h]; NodoHash*prev=nullptr; while(cur){ if(cur->key==k){ if(prev) prev->sig=cur->sig; else tabla[h]=cur->sig; delete cur; --n; return true; } prev=cur; cur=cur->sig; } return false; }
int& HashTableInt::at(int k){ int h=hash(k); for(NodoHash*cur=tabla[h];cur;cur=cur->sig) if(cur->key==k) return cur->value; throw runtime_error("Clave no encontrada"); }
const int& HashTableInt::at(int k)const{ int h=hash(k); for(NodoHash*cur=tabla[h];cur;cur=cur->sig) if(cur->key==k) return cur->value; throw runtime_error("Clave no encontrada"); }
void HashTableInt::imprimir()const{ cout<<"Tabla hash (cap="<<cap<<"):\n"; for(int i=0;i<cap;++i){ cout<<i<<": "; for(NodoHash*cur=tabla[i];cur;cur=cur->sig) cout<<"("<<cur->key<<"->"<<cur->value<<") "; cout<<"\n"; } }
void HashTableInt::clear(){ for(int i=0;i<cap;++i){ NodoHash*cur=tabla[i]; while(cur){ NodoHash*nx=cur->sig; delete cur; cur=nx; } tabla[i]=nullptr; } n=0; }
