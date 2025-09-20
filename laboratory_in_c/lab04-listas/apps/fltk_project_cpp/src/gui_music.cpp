#include "gui_music.hpp"

void append(Node*& head, const std::string& song) {
    Node* n = new Node(song);
    if (!head) { head = n; return; }
    Node* t = head;
    while (t->next) t = t->next;
    t->next = n;
}

Node* find_prev(Node* head, Node* node) {
    if (!head || head == node) return nullptr;
    Node* t = head;
    while (t && t->next != node) t = t->next;
    return t;
}

void clear_list(Node*& head) {
    Node* t = head;
    while (t) {
        Node* nx = t->next;
        delete t;
        t = nx;
    }
    head = nullptr;
}
