#include "pila_como_vector.h" 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>  

// Interfaces no disponibles para nuestros clientes (quienes usan nuestra estructura), es decir, para quien usa nuestro TAD.

struct pila {
    int tamano;    // numero maximo de elementos que podemos almacenar en el vector.
    int cantidad;  // cantidad actual de elementos almacenados
    int *datos;    // vector de int que representa nuestros datos. 
};

// Si el vector esta lleno, aumentamos 2 veces su tamano.
void aumentar_pila(Pila *pila) {
    
    printf("Aumentando 2 veces el tamaño actual del vector (2 * %d)\n", pila->tamano);

    int *temp = pila->datos; 

    pila->tamaño = pila->tamano * 2;

    pila->datos = (int*)calloc(pila->tamano, sizeof(int)); 

    for (int i = 0; i < pila->cantidad; i++ ) {  // Aqui era un error recorrer hasta tamano, debe ser cantidad
        pila->datos[i] = temp[i];
    }
    free(temp);
}

// Disminuir el tamano del vector a la mitad cuando tenga 1/4 o 25% lleno   
void disminuir_pila(Pila *pila) {

    if ((pila->cantidad < pila->tamano / 4) && 
        (pila->tamano >= 4)) { 
       
        printf("Disminuyendo el tamano actual del vector a la mitad (%d / 2)\n", pila->tamano); 
 
        int *temp = pila->datos; 
        pila->tamano /= 2;

        pila->datos = (int*)calloc(pila->tamano, sizeof(int)); 

        for (int j = 0; j < pila->cantidad; j++ ) { // Aquí también debe ser cantidad
            pila->datos[j] = temp[j];
        }
        free(temp);
    }
}

bool esta_llena_pila(Pila *pila) {
   
    return (pila->tamano == pila->cantidad);
}

// Interfaces disponibles para nuestros clientes, quienes usan nuestro TAD.

Pila* crear_pila(int tamano) {

    Pila *pila = (Pila*) malloc(sizeof(Pila));
    pila->cantidad = 0;
    pila->tamano = tamano;
    pila->datos = (int*) calloc(tamano, sizeof(int));
    
    return pila;
}

void destruir_pila(Pila **pila_direccion) {

    Pila *pila = *pila_direccion;
    free(pila->datos);
    free(pila);
    *pila_direccion = NULL;
}
 
void apilar_pila(Pila *pila, int valor) {

    if (esta_llena_pila(pila)) {
        aumentar_pila(pila);
    } 
    pila->datos[pila->cantidad] = valor;
    pila->cantidad++;
}

void desapilar_pila(Pila *pila) { 
        
    if (pila->cantidad == 0) {
        printf("La pila esta vacia, no se puede desapilar.\n");
        return;
    }

    pila->cantidad--; // decrementa la cantidad     
    disminuir_pila(pila);
}

int tamaño_pila(const Pila *pila) {
    
    return pila->tamano;
}

int cantidad_pila(const Pila *pila) {
 
    return pila->cantidad;
}

void imprimir_pila(const Pila *pila) {

    printf("Pila = { ");       
    for (int i = pila->cantidad - 1; i >= 0; i--) {

        printf("%d", pila->datos[i]);

        if (i > 0)
            printf(" -> ");
    }
    printf(" } \n\n");
}
