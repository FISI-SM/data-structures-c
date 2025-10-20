# Pila (Stack) con arreglo dinámico en C++ (sin std::vector)

Implementación de `PilaArray<T>` usando `new[]/delete[]`, con crecimiento automático de capacidad (doblando cuando se llena).

## API principal
- `push(const T&)`
- `pop()` *(lanza excepción si está vacía)*
- `top()` / `top() const`
- `empty()`, `size()`, `capacity()`
- `clear()`, `reservar(size_t)`, `shrink_to_fit()`
- `imprimir()`

## Compilar y ejecutar
```bash
make
./bin/app_pila_array
```

> Nota: Al ser `template`, toda la lógica está en `include/pila_array.h`.
