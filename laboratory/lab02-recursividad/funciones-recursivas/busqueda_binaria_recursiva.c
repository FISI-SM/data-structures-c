#include <stdio.h>


int busqueda_binaria_recursiva_vector_dinamico(int *datos, int limite_izquierda, int limite_derecha, int valor) {    
    
    int index_medio = (limite_izquierda + limite_derecha) / 2;

    printf("Indice del medio %d\n\n", index_medio);

    if (limite_izquierda > limite_derecha) //caso base 1
       return -1;
    
    if (datos[index_medio] == valor) //caso base 2
       return index_medio; 

    else if (datos[index_medio] < valor)   
       return busqueda_binaria_recursiva_vector_dinamico(datos, index_medio + 1, limite_derecha, valor);

    else 
       return busqueda_binaria_recursiva_vector_dinamico(datos, limite_izquierda, index_medio - 1, valor);

    return -1;
}

int main() {
    
    int elementos[10] = {1, 3, 5, 10, 20, 23, 30, 40, 50, 55};
    
    int valor = 10;

    int index = busqueda_binaria_recursiva_vector_dinamico(elementos, 0, 9, valor);

    printf("valor buscado = %d | indice retornado = %d  \n\n", valor, index); 

    return 0;
}
