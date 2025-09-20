#include "hash_table.h"
#include <string>

int main() {
    HashTable<std::string, int> H(4);

    H.insert("uno", 1);
    H.insert("dos", 2);
    H.insert("tres", 3);
    H.imprimir();

    H.insert("dos", 22); // actualización
    H.imprimir();

    if (H.contains("tres")) {
        printf("tres -> %d\n", H.at("tres"));
    }

    H.erase("uno");
    H.imprimir();

    // Fuerza rehash
    H.insert("cuatro", 4);
    H.insert("cinco", 5);
    H.insert("seis", 6);
    H.imprimir();

    return 0;
}
