#include "bplustree_map.h"
#include <iostream>

int main() {
    BPlusTree T(4); // orden 4 (máx 4 claves por nodo)

    // Insertar varias claves (notar splits)
    for (int k : {10, 20, 5, 6, 12, 30, 7, 17, 3, 25, 1, 15}) {
        T.insert(k, k*100);
        T.printLeaves();
    }

    // Consultas
    for (int k : {1, 7, 15, 30}) {
        std::cout << "at(" << k << ") = " << T.at(k) << "\n";
    }
    std::cout << "contains(8)? " << (T.contains(8) ? "si" : "no") << "\n";

    return 0;
}
