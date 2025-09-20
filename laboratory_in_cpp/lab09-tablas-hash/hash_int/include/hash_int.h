#ifndef HASH_INT_H
#define HASH_INT_H
#include <iostream>
#include <stdexcept>
using namespace std;
struct NodoHash {
    int key; int value; NodoHash* sig;
    NodoHash(int k,int v):key(k),value(v),sig(nullptr){}
};
struct HashTableInt{
    NodoHash** tabla; int cap; int n;
    HashTableInt(int capacidad=8);
    ~HashTableInt();
    int hash(int k)const{return k%cap;}
    void insertar(int k,int v); bool contiene(int k)const;
    bool eliminar(int k); int& at(int k); const int& at(int k)const;
    void imprimir()const; void clear();
};
#endif
