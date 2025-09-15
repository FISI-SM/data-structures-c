#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *array;      // puntero al arreglo
    int capacity;    // capacidad máxima
    int size;        // elementos actuales
} SimpleArray;

// ------------------ Funciones auxiliares ------------------
SimpleArray* create_array(int capacity) {
    SimpleArray *arr = (SimpleArray*)malloc(sizeof(SimpleArray));
    arr->capacity = capacity;
    arr->size = 0;
    arr->array = (int*)malloc(sizeof(int) * capacity);
    return arr;
}

bool is_empty(SimpleArray *arr) {
    return arr->size == 0;
}

bool is_full(SimpleArray *arr) {
    return arr->size == arr->capacity;
}

// ------------------ Operaciones ------------------
void push_back(SimpleArray *arr, int data) {
    if (is_full(arr)) {
        printf("Error: Array lleno\n");
        return;
    }
    int insert_index = arr->size;     // 1) calcular índice libre
    arr->array[insert_index] = data;  // 2) escribir el dato
    arr->size++;                      // 3) crecer el tamaño
}

void push_front(SimpleArray *arr, int data) {
    if (is_full(arr)) {
        printf("Error: Array lleno\n");
        return;
    }
    for (int i = arr->size; i > 0; i--) {
        int dst = i;
        int src = i - 1;
        arr->array[dst] = arr->array[src];
    }
    int first_index = 0;
    arr->array[first_index] = data;
    arr->size++;
}

int pop_back(SimpleArray *arr) {
    if (is_empty(arr)) {
        printf("Error: Array vacío\n");
        return -1;
    }
    int last_index = arr->size - 1;     // 1) calcular último índice válido
    int value = arr->array[last_index];  // 2) leer el valor
    arr->size--;                         // 3) decrementar tamaño
    return value;
}

int pop_front(SimpleArray *arr) {
    if (is_empty(arr)) {
        printf("Error: Array vacío\n");
        return -1;
    }
    int first_index = 0;
    int value = arr->array[first_index];

    for (int i = 1; i < arr->size; i++) {
        int dst = i - 1;
        int src = i;
        arr->array[dst] = arr->array[src];
    }
    arr->size--;
    return value;
}

void insert(SimpleArray *arr, int data, int position) {
    if (is_full(arr)) {
        printf("Error: Array lleno\n");
        return;
    }
    if (position < 0 || position > arr->size) {
        printf("Error: Posición fuera de rango\n");
        return;
    }
    for (int i = arr->size; i > position; i--) {
        int dst = i;
        int src = i - 1;
        arr->array[dst] = arr->array[src];
    }
    int insert_index = position;
    arr->array[insert_index] = data;
    arr->size++;
}

int remove_at(SimpleArray *arr, int position) {
    if (is_empty(arr)) {
        printf("Error: Array vacío\n");
        return -1;
    }
    if (position < 0 || position >= arr->size) {
        printf("Error: Posición fuera de rango\n");
        return -1;
    }
    int remove_index = position;
    int value = arr->array[remove_index];

    for (int i = position + 1; i < arr->size; i++) {
        int dst = i - 1;
        int src = i;
        arr->array[dst] = arr->array[src];
    }
    arr->size--;
    return value;
}

// ------------------ Impresión ------------------
void print_array(SimpleArray *arr) {
    printf("[");
    int last_index = arr->size - 1;  // para el separador
    for (int i = 0; i < arr->size; i++) {
        int read_index = i;
        printf("%d", arr->array[read_index]);
        if (i < last_index) printf(", ");
    }
    printf("]\n");
}

// ------------------ Ejemplo de uso ------------------
int main() {
    SimpleArray *arr = create_array(5);

    push_back(arr, 10);
    push_back(arr, 20);
    push_front(arr, 5);
    print_array(arr);  // [5, 10, 20]

    insert(arr, 15, 2);
    print_array(arr);  // [5, 10, 15, 20]

    printf("Pop front: %d\n", pop_front(arr)); // 5
    printf("Pop back: %d\n", pop_back(arr));   // 20

    print_array(arr);  // [10, 15]

    free(arr->array);
    free(arr);

    return 0;
}
