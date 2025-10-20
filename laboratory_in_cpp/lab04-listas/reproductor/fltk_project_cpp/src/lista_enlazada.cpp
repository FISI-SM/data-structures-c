#include "lista_enlazada.h"

void ListaEnlazada::append(const std::string & title) {
    Node *n = new Node(title);
    if (!head) {
        head = n;
        current = head;
        return;
    }
    Node *t = head;
    
    while (t -> next) 
        t = t -> next;
    t -> next = n;
}

Node *ListaEnlazada::find_prev(Node *node) {
    if (!head || head == node) 
        return nullptr;
    Node *t = head;
    
    while (t && t -> next != node) 
        t = t -> next;

    return t;
}

void ListaEnlazada::move_left() {
    if (!current)
        return;
    
    Node *prev = find_prev(current);
    
    if (prev) 
        current = prev;
}

void ListaEnlazada::move_right() {
    if (current && current -> next) 
        current = current -> next;
}

const char *ListaEnlazada::title_cstr() const {
    static std::string empty = "No songs";
    return current ? current -> song.c_str() : empty.c_str();
}

ListaEnlazada::~ListaEnlazada() {
    Node *t = head;
    while (t) {
        Node *nx = t -> next;
        delete t;
        t = nx;
    }
    head = current = nullptr;
}