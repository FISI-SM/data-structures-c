# Pila (Stack) usando Lista Enlazada en C++

Implementación de una **pila genérica** (`PilaLista<T>`) sobre una lista enlazada simple.

## API principal
- `push(const T&)`
- `pop()` *(lanza excepción si está vacía)*
- `top()` / `top() const`
- `empty()`, `size()`
- `clear()`
- `imprimir()`

## Compilar y ejecutar
```bash
make
./bin/app_pila_lista
```

> Nota: al ser `template`, la implementación está en el header `include/pila_lista.h`.
