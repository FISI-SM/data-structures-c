#include "pila_array_int.h"

int main() {
    PilaArrayInt P(4);
    P.push(10); P.push(20); P.push(30);
    P.imprimir();
    cout << "Top: " << P.top() << "\n";
    P.pop(); P.imprimir();
    cout << "Size: " << P.size() << ", Cap: " << P.capacity() << "\n";
    P.clear();
    cout << "Empty? " << (P.empty() ? "si" : "no") << "\n";
    return 0;
}
