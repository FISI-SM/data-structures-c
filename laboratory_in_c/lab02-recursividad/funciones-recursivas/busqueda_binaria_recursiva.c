/**
 * ------------------------------------------------------------
 *   Programa: Búsqueda Binaria Recursiva
 *
 *   Descripción:
 *   Este programa implementa el algoritmo de búsqueda binaria
 *   de manera recursiva sobre un arreglo de enteros ordenado.
 *
 *   Funcionamiento:
 *   - La función `busquedaBinariaRecursiva` recibe:
 *       * arreglo: arreglo de enteros ordenados
 *       * izquierda: índice inicial del rango de búsqueda
 *       * derecha: índice final del rango de búsqueda
 *       * objetivo: número a buscar en el arreglo
 *
 *   - En cada llamada:
 *       1. Si izquierda > derecha → no se encontró el valor → retorna -1.
 *       2. Si el valor está en la posición media → retorna ese índice.
 *       3. Si el valor es mayor que el del medio → busca en la mitad derecha.
 *       4. Si el valor es menor → busca en la mitad izquierda.
 *
 *   Ejemplo:
 *   Arreglo: {1, 3, 5, 10, 20, 23, 30, 40, 50, 55}
 *   Objetivo: 10
 *   Resultado esperado: índice 3
 * ------------------------------------------------------------
 */

#include <stdio.h>

int busquedaBinariaRecursiva(int *arreglo, int izquierda, int derecha, int objetivo) {    
    
    int medio = (izquierda + derecha) / 2;

    printf("Índice del medio: %d\n\n", medio);

    if (izquierda > derecha) // caso base 1
        return -1;
    
    if (arreglo[medio] == objetivo) // caso base 2
        return medio; 

    else if (arreglo[medio] < objetivo)   
        return busquedaBinariaRecursiva(arreglo, medio + 1, derecha, objetivo);

    else 
        return busquedaBinariaRecursiva(arreglo, izquierda, medio - 1, objetivo);
}

int main() {
    
    int numeros[10] = {1, 3, 5, 10, 20, 23, 30, 40, 50, 55};
    
    int objetivo = 10;

    int posicion = busquedaBinariaRecursiva(numeros, 0, 9, objetivo);

    printf("Valor buscado = %d | Índice retornado = %d\n\n", objetivo, posicion); 

    return 0;
}
