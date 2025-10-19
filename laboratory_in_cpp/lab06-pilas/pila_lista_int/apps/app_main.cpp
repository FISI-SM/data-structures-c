#include "pila_lista_int.h"

int main() {
    
    PilaListaInt P;
    P.push(10); 
    P.push(20); 
    P.push(30);
    P.imprimir();
    
    cout << "Top: " << P.top() << "\n";
    P.pop(); 
    P.imprimir();
    
    cout << "Size: " << P.size() << "\n";
    
    cout<<"Cleaning...\n";
    P.clear();
    
    cout << "Empty? " << (P.empty() ? "si" : "no") << "\n";
    
    return 0;
}
