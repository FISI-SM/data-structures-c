#include "cola_array.h"

int main() {
    ColaArray<int> Q(4);

    Q.push(10);
    Q.push(20);
    Q.push(30);
    Q.imprimir(); // 10 20 30

    std::cout << "front=" << Q.front() << ", back=" << Q.back() << "\n";

    Q.pop();      // quita 10
    Q.imprimir(); // 20 30

    Q.push(40);
    Q.push(50);   // forzará crecer si es necesario
    Q.imprimir();

    while (!Q.empty()) {
        std::cout << "pop " << Q.front() << "\n";
        Q.pop();
    }

    // Excepción esperada
    try { Q.pop(); } catch (const std::exception& e) {
        std::cout << "Excepcion: " << e.what() << "\n";
    }

    return 0;
}
