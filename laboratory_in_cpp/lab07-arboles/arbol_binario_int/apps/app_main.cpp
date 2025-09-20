#include "arbol_binario_int.h"
int main(){
    ArbolBinario A;
    for(int v: {10,20,30,40,50,60,70}) A.insertarCompleto(v);
    cout<<"Pre: ";A.preorden(); cout<<"In: ";A.inorden(); cout<<"Post: ";A.postorden();
    cout<<"Niveles: ";A.porNiveles(); cout<<"Altura: "<<A.altura()<<"\n"; cout<<"Nodos: "<<A.contarNodos()<<"\n";
    A.reflejar(); cout<<"In(reflejado): "; A.inorden();
    A.liberar(); cout<<"Tras liberar: "; A.porNiveles();
    return 0;
}
