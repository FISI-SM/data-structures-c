#include "abb_int.h"
int main(){
    ABB T; for(int v: {50,30,70,20,40,60,80}) T.insertar(v);
    cout<<"In: ";T.inorden(); cout<<"Pre: ";T.preorden(); cout<<"Post: ";T.postorden();
    cout<<"Niveles: ";T.porNiveles(); cout<<"Min="<<T.minimo()<<", Max="<<T.maximo()<<"\n";
    cout<<"Eliminar 70...\n"; T.eliminar(70); cout<<"In: "; T.inorden(); cout<<"Niveles: "; T.porNiveles();
    T.liberar(); cout<<"Tras liberar: "; T.porNiveles(); return 0;
}
