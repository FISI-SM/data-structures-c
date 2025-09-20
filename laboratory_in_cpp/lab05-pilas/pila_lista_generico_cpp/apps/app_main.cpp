#include "pila_lista.h"

int main() {
    PilaLista<int> P;

    P.push(10);
    P.push(20);
    P.push(30);
    P.imprimir(); // 30 20 10

    int t = P.top();
    std::cout << "Top: " << t << "\n";

    P.pop();
    P.imprimir(); // 20 10

    std::cout << "Size: " << P.size() << "\n";

    P.clear();
    std::cout << "Empty? " << (P.empty() ? "si" : "no") << "\n";

    try {
        P.pop();
    } catch (const std::exception& e) {
        std::cout << "Excepcion esperada: " << e.what() << "\n";
    }

    return 0;
}
