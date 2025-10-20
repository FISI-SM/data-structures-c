#include "pila_array.h"

int main() {
    PilaArray<int> P(4);

    P.push(10);
    P.push(20);
    P.push(30);
    P.imprimir(); // 30 20 10

    // Capacidad crece automáticamente
    P.push(40);
    P.push(50);
    P.imprimir();

    // Top / Pop
    int t = P.top();
    std::cout << "Top: " << t << "\n";
    P.pop();
    P.imprimir();

    std::cout << "Size: " << P.size() << ", Cap: " << P.capacity() << "\n";

    // Shrink
    P.clear();
    P.shrink_to_fit();
    std::cout << "Empty? " << (P.empty() ? "si" : "no") << ", Cap: " << P.capacity() << "\n";

    // Excepción esperada
    try {
        P.pop();
    } catch (const std::exception& e) {
        std::cout << "Excepcion: " << e.what() << "\n";
    }

    return 0;
}
