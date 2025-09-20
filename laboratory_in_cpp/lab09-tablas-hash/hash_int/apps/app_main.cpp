#include "hash_int.h"
int main(){ HashTableInt H(5); H.insertar(1,100); H.insertar(6,200); H.insertar(11,300); H.imprimir(); if(H.contiene(6)) cout<<"6->"<<H.at(6)<<"\n"; H.eliminar(6); H.imprimir(); try{ cout<<H.at(6)<<"\n"; }catch(const exception&e){ cout<<"Excepcion esperada: "<<e.what()<<"\n"; } H.clear(); H.imprimir(); return 0; }
