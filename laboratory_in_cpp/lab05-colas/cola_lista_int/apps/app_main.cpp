#include "cola_lista_int.h"

int main() {
    ColaListaInt Q;
    Q.push(10); 
    Q.push(20); 
    Q.push(30);
    Q.imprimir();
    
    std::cout << "front=" << Q.front() << ", back=" << Q.back() << "\n";

    Q.pop(); 
    Q.imprimir();
    Q.push(40); 
    Q.push(50);
    Q.imprimir();

    while (!Q.empty()) {
        std::cout << "pop " << Q.front() << "\n";
        Q.pop();
    }

    try { Q.back(); } catch (const std::exception& e) {
        std::cout << "Excepcion esperada: " << e.what() << "\n";
    }
    return 0;
}
