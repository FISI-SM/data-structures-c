#include "cola_array_int.h"

int main() {
    ColaArrayInt Q(4);
    Q.push(10); Q.push(20); Q.push(30);
    Q.imprimir();
    std::cout << "front=" << Q.front() << ", back=" << Q.back() << "\n";

    Q.pop(); Q.imprimir();
    Q.push(40); Q.push(50); // crecimiento
    Q.imprimir();

    while (!Q.empty()) {
        std::cout << "pop " << Q.front() << "\n";
        Q.pop();
    }

    try { Q.front(); } catch (const std::exception& e) {
        std::cout << "Excepcion esperada: " << e.what() << "\n";
    }
    return 0;
}
