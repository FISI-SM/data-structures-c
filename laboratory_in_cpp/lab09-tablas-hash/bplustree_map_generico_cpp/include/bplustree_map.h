#ifndef BPLUSTREE_MAP_H
#define BPLUSTREE_MAP_H

#include <vector>
#include <algorithm>
#include <iostream>
#include <stdexcept>

// Implementación sencilla de un Árbol B+ para pares (K,V) con K=int y V=int,
// para fines didácticos. Soporta insertar y buscar.
// Orden (máx claves por nodo) pequeño para simplificar.

struct BPlusNode {
    bool leaf;
    std::vector<int> keys;          // claves
    std::vector<BPlusNode*> child;  // hijos (interno): size = keys.size()+1
    std::vector<int> values;        // valores (solo en hojas), paralelos a keys
    BPlusNode* next;                // encadenamiento de hojas

    BPlusNode(bool isLeaf, int order)
        : leaf(isLeaf), next(nullptr) {
        keys.reserve(order);
        if (!leaf) child.reserve(order+1);
        else values.reserve(order);
    }
};

struct BPlusTree {
    int order;        // número máximo de claves en un nodo
    BPlusNode* root;

    BPlusTree(int ord = 4) : order(ord), root(nullptr) {
        if (order < 3) order = 3;
    }

    ~BPlusTree() { clear(); }

    void clear() { clearRec(root); root = nullptr; }

    // Inserta (k,v) (si k existe, actualiza v)
    void insert(int k, int v) {
        if (!root) {
            root = new BPlusNode(true, order);
            root->keys.push_back(k);
            root->values.push_back(v);
            return;
        }
        // Si la raíz se divide, crear nueva raíz
        BPlusNode* newChild = nullptr;
        int upKey = 0;
        bool split = insertRec(root, k, v, newChild, upKey);
        if (split) {
            BPlusNode* newRoot = new BPlusNode(false, order);
            newRoot->keys.push_back(upKey);
            newRoot->child.push_back(root);
            newRoot->child.push_back(newChild);
            root = newRoot;
        }
    }

    // Busca valor por clave; lanza si no está
    int at(int k) const {
        BPlusNode* n = root;
        while (n && !n->leaf) {
            size_t i = upper_bound(n->keys.begin(), n->keys.end(), k) - n->keys.begin();
            n = n->child[i];
        }
        if (!n) throw std::out_of_range("clave no encontrada");
        auto it = std::lower_bound(n->keys.begin(), n->keys.end(), k);
        if (it == n->keys.end() || *it != k) throw std::out_of_range("clave no encontrada");
        size_t pos = it - n->keys.begin();
        return n->values[pos];
    }

    bool contains(int k) const {
        try { (void)at(k); return true; }
        catch (...) { return false; }
    }

    void printLeaves() const {
        const BPlusNode* n = root;
        if (!n) { std::cout << "[]\n"; return; }
        while (n && !n->leaf) n = n->child.front();
        std::cout << "Hojas: ";
        while (n) {
            std::cout << "[";
            for (size_t i = 0; i < n->keys.size(); ++i) {
                std::cout << n->keys[i] << ":" << n->values[i];
                if (i+1<n->keys.size()) std::cout << ",";
            }
            std::cout << "] -> ";
            n = n->next;
        }
        std::cout << "NULL\n";
    }

private:
    bool insertRec(BPlusNode* node, int k, int v, BPlusNode*& newChild, int& upKey) {
        if (node->leaf) {
            // Insertar/actualizar en hoja
            auto it = std::lower_bound(node->keys.begin(), node->keys.end(), k);
            size_t pos = it - node->keys.begin();
            if (it != node->keys.end() && *it == k) {
                node->values[pos] = v; // actualizar
                return false;
            }
            node->keys.insert(it, k);
            node->values.insert(node->values.begin()+pos, v);

            if ((int)node->keys.size() > order) {
                // dividir hoja
                int mid = node->keys.size()/2;
                BPlusNode* right = new BPlusNode(true, order);
                right->keys.assign(node->keys.begin()+mid, node->keys.end());
                right->values.assign(node->values.begin()+mid, node->values.end());
                node->keys.resize(mid);
                node->values.resize(mid);

                right->next = node->next;
                node->next = right;

                newChild = right;
                upKey = right->keys.front(); // promovemos primera clave de la derecha
                return true;
            }
            return false;
        } else {
            // Nodo interno: bajar al hijo adecuado
            size_t i = std::upper_bound(node->keys.begin(), node->keys.end(), k) - node->keys.begin();
            BPlusNode* child = node->child[i];
            BPlusNode* childNew = nullptr;
            int promoted = 0;
            bool split = insertRec(child, k, v, childNew, promoted);
            if (split) {
                // insertar promoted en este interno
                auto it = std::upper_bound(node->keys.begin(), node->keys.end(), promoted);
                size_t pos = it - node->keys.begin();
                node->keys.insert(it, promoted);
                node->child.insert(node->child.begin()+pos+1, childNew);

                if ((int)node->keys.size() > order) {
                    // dividir interno
                    int mid = node->keys.size()/2;
                    BPlusNode* right = new BPlusNode(false, order);
                    // keys para la derecha: desde mid+1
                    right->keys.assign(node->keys.begin()+mid+1, node->keys.end());
                    // hijos para la derecha: desde mid+1
                    right->child.assign(node->child.begin()+mid+1, node->child.end());
                    // clave promovida hacia arriba
                    upKey = node->keys[mid];

                    node->keys.resize(mid);
                    node->child.resize(mid+1);

                    newChild = right;
                    return true;
                }
            }
            return false;
        }
    }

    void clearRec(BPlusNode* node) {
        if (!node) return;
        if (!node->leaf) {
            for (auto* ch : node->child) clearRec(ch);
        }
        delete node;
    }
};

#endif
