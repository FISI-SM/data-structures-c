#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <vector>
#include <list>
#include <functional>
#include <stdexcept>
#include <iostream>

// Tabla hash genérica con encadenamiento separado (separate chaining).
// Requiere que exista std::hash<K> y operator== para K.
template <typename K, typename V>
struct HashTable {
    using Bucket = std::list<std::pair<K,V>>;

    std::vector<Bucket> buckets;
    size_t n_elems;
    float  max_load; // umbral para rehash

    HashTable(size_t cap_inicial = 8, float max_load_factor = 0.75f)
        : buckets(cap_inicial), n_elems(0), max_load(max_load_factor) {}

    size_t size() const { return n_elems; }
    bool empty() const { return n_elems == 0; }
    size_t bucket_count() const { return buckets.size(); }
    float load_factor() const { return (float)n_elems / (float)buckets.size(); }

    void clear() {
        for (auto& b : buckets) b.clear();
        n_elems = 0;
    }

    // Inserta o actualiza
    void insert(const K& k, const V& v) {
        size_t idx = hash_idx(k);
        for (auto& kv : buckets[idx]) {
            if (kv.first == k) { kv.second = v; return; }
        }
        buckets[idx].push_back({k,v});
        ++n_elems;
        if (load_factor() > max_load) rehash(buckets.size() * 2);
    }

    // Elimina; retorna true si existía
    bool erase(const K& k) {
        size_t idx = hash_idx(k);
        for (auto it = buckets[idx].begin(); it != buckets[idx].end(); ++it) {
            if (it->first == k) {
                buckets[idx].erase(it);
                --n_elems;
                return true;
            }
        }
        return false;
    }

    bool contains(const K& k) const {
        size_t idx = hash_idx(k);
        for (const auto& kv : buckets[idx]) if (kv.first == k) return true;
        return false;
    }

    V& at(const K& k) {
        size_t idx = hash_idx(k);
        for (auto& kv : buckets[idx]) if (kv.first == k) return kv.second;
        throw std::out_of_range("clave no encontrada");
    }

    const V& at(const K& k) const {
        size_t idx = hash_idx(k);
        for (const auto& kv : buckets[idx]) if (kv.first == k) return kv.second;
        throw std::out_of_range("clave no encontrada");
    }

    // Rehash explícito
    void rehash(size_t nueva_cap) {
        if (nueva_cap < 1) nueva_cap = 1;
        std::vector<Bucket> nueva(nueva_cap);
        for (auto& b : buckets) {
            for (auto& kv : b) {
                size_t idx = std::hash<K>{}(kv.first) % nueva_cap;
                nueva[idx].push_back(std::move(kv));
            }
        }
        buckets.swap(nueva);
    }

    void imprimir() const {
        std::cout << "HashTable (buckets=" << buckets.size() << ", n=" << n_elems 
                  << ", load=" << load_factor() << ")\n";
        for (size_t i = 0; i < buckets.size(); ++i) {
            std::cout << i << ": ";
            for (const auto& kv : buckets[i]) {
                std::cout << "{" << kv.first << ":" << kv.second << "} -> ";
            }
            std::cout << "NULL\n";
        }
    }

private:
    size_t hash_idx(const K& k) const {
        return std::hash<K>{}(k) % buckets.size();
    }
};

#endif
