#ifndef GUI_MUSIC_HPP
#define GUI_MUSIC_HPP

#include <string>

struct Node {
    std::string song;
    Node* next;
    explicit Node(const std::string& s) : song(s), next(nullptr) {}
};

// Inserta al final de la lista
void append(Node*& head, const std::string& song);

// Devuelve el nodo anterior a 'node' (o nullptr si es el primero/no existe)
Node* find_prev(Node* head, Node* node);

// Libera toda la lista
void clear_list(Node*& head);

#endif
