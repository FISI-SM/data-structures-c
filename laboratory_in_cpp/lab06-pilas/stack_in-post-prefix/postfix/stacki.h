#ifndef STACKI_H
#define STACKI_H

#include <stdlib.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0

typedef struct {
    int *data;
    int top;
    int capacity;
} stacki;

static inline int stacki_init(stacki *s, int capacity) {
    if (capacity <= 0) capacity = 10;
    s->data = (int *)malloc(capacity * sizeof(int));
    if (s->data == NULL) return FALSE;
    s->top = -1;
    s->capacity = capacity;
    return TRUE;
}

static inline void stacki_deinit(stacki *s) {
    if (s->data != NULL) free(s->data);
    s->data = NULL;
    s->top = -1;
    s->capacity = 0;
}

static inline int stacki_empty(const stacki *s) {
    return (s->top < 0);
}

static inline int stacki_full(const stacki *s) {
    return (s->top >= s->capacity - 1);
}

static inline int stacki_push(stacki *s, int value) {
    if (stacki_full(s)) {
        int new_capacity = s->capacity * 2;
        int *new_data = (int *)realloc(s->data, new_capacity * sizeof(int));
        if (new_data == NULL) return FALSE;
        s->data = new_data;
        s->capacity = new_capacity;
    }
    s->data[++(s->top)] = value;
    return TRUE;
}

static inline int stacki_pop(stacki *s) {
    if (stacki_empty(s)) {
        fprintf(stderr, "stack underflow\n");
        return 0;
    }
    return s->data[(s->top)--];
}

static inline int stacki_stacktop(const stacki *s) {
    if (stacki_empty(s)) {
        fprintf(stderr, "stack empty\n");
        return 0;
    }
    return s->data[s->top];
}

#endif /* STACKI_H */
