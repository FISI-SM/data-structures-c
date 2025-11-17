# Grafo con Lista de Adyacencia (lista enlazada) en C++

Implementa `GrafoLista` ponderado con un arreglo de punteros a listas (`NodoAdj`). Operaciones: `agregarArista`, `eliminarArista`, `existeArista`, `imprimir`, `floydWarshall`.

## Algoritmo de Floyd-Warshall

El algoritmo de Floyd-Warshall encuentra el camino más corto entre todos los pares de vértices en un grafo ponderado. Utiliza programación dinámica con una complejidad de O(V³), donde V es el número de vértices.

### Características:
- Encuentra distancias mínimas entre todos los pares de vértices
- Puede manejar grafos dirigidos y no dirigidos
- Detecta caminos más cortos incluso con pesos negativos (pero no ciclos negativos)
- Retorna una matriz de distancias donde dist[i][j] es la distancia más corta del vértice i al vértice j

## Compilar y ejecutar
```bash
make
./bin/app_grafo_lista
```