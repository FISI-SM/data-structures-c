#include "cola_lista.h"

int main() {
    ColaLista<int> Q;

    Q.push(10);
    Q.push(20);
    Q.push(30);
    Q.imprimir(); // 10 20 30

    std::cout << "front=" << Q.front() << ", back=" << Q.back() << "\n";

    Q.pop();      // quita 10
    Q.imprimir(); // 20 30

    Q.push(40);
    Q.push(50);
    Q.imprimir(); // 20 30 40 50

    while (!Q.empty()) {
        std::cout << "pop " << Q.front() << "\n";
        Q.pop();
    }

    // Excepción esperada
    try { Q.front(); } catch (const std::exception& e) {
        std::cout << "Excepcion: " << e.what() << "\n";
    }

    return 0;
}
