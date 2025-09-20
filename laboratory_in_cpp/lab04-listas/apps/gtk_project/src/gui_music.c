#include "gui_music.h"
#include <stdlib.h>
#include <string.h>

#ifndef _WIN32
static char* _strdup(const char* s) {
    char *d = malloc(strlen(s) + 1);
    if (d) strcpy(d, s);
    return d;
}
#else
#define _strdup strdup
#endif

Node* create_node(const char *song) {
    Node *n = (Node*)malloc(sizeof(Node));
    n->song = _strdup(song);
    n->next = NULL;
    return n;
}

void append(Node **head_ref, const char *song) {
    Node *n = create_node(song);
    if (*head_ref == NULL) {
        *head_ref = n;
        return;
    }
    Node *t = *head_ref;
    while (t->next) t = t->next;
    t->next = n;
}

Node* find_prev(Node *head, Node *node) {
    if (head == NULL || head == node) return NULL;
    Node *t = head;
    while (t && t->next != node) t = t->next;
    return t;
}
