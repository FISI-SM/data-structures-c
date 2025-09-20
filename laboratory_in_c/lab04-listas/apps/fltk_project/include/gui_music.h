#ifndef GUI_MUSIC_H
#define GUI_MUSIC_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Node {
    char *song;
    struct Node *next;
} Node;

Node* create_node(const char *song);
void append(Node **head_ref, const char *song);
Node* find_prev(Node *head, Node *node);

#ifdef __cplusplus
}
#endif

#endif
