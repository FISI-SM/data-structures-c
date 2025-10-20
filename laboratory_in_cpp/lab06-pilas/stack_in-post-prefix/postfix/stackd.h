#ifndef STACKD_H
#define STACKD_H

#include <stdlib.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0

typedef struct {
    int *data;
    int top;
    int capacity;
} stackd;

static inline int stackd_init(stackd *s, int capacity) {
    if (capacity <= 0) capacity = 10;
    s->data = (int *)malloc(capacity * sizeof(int));
    if (s->data == NULL) return FALSE;
    s->top = -1;
    s->capacity = capacity;
    return TRUE;
}

static inline void stackd_deinit(stackd *s) {
    if (s->data != NULL) free(s->data);
    s->data = NULL;
    s->top = -1;
    s->capacity = 0;
}

static inline int stackd_empty(const stackd *s) {
    return (s->top < 0);
}

static inline int stackd_full(const stackd *s) {
    return (s->top >= s->capacity - 1);
}

static inline int stackd_push(stackd *s, int value) {
    if (stackd_full(s)) {
        int new_capacity = s->capacity * 2;
        int *new_data = (int *)realloc(s->data, new_capacity * sizeof(int));
        if (new_data == NULL) return FALSE;
        s->data = new_data;
        s->capacity = new_capacity;
    }
    s->data[++(s->top)] = value;
    return TRUE;
}

static inline int stackd_pop(stackd *s) {
    if (stackd_empty(s)) {
        fprintf(stderr, "stack underflow\n");
        return 0;
    }
    return s->data[(s->top)--];
}

static inline int stackd_peek(const stackd *s) {
    if (stackd_empty(s)) {
        fprintf(stderr, "stack empty\n");
        return 0;
    }
    return s->data[s->top];
}

#endif /* STACKD_H */
