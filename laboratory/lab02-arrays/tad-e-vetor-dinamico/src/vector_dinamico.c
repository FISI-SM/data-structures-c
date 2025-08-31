#include "vector_dinamico.h" 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>  

// Interfaces no disponibles para nuestros clientes (quienes usan nuestra estructura), en este caso quienes usaran nuestro TAD.

struct vector_dinamico {
    bool ordenado;  // true indica que se quiere mantener el vector ordenado. 
    int tamano;     // numero maximo de elementos que podemos almacenar en el vector.
    int cantidad;   // cantidad actual de elementos almacenados.
    int *datos;     // vector de enteros que representa nuestros datos. 
};

bool esta_lleno_vector_dinamico(Vector_Dinamico* vector_dinamico) {
   
    return (vector_dinamico->tamano == vector_dinamico->cantidad);

}

// Si el vector esta lleno, aumentamos 2 veces su tamano.
void aumentar_vector_dinamico(Vector_Dinamico *vector_dinamico) {
    
    printf("Aumentando 2 veces el tamano actual del vector( 2 * %d )\n", vector_dinamico->tamano);

    int *temp = vector_dinamico->datos; 
    //vector_dinamico->tamano *= 2;
    vector_dinamico->tamano = vector_dinamico->tamano * 2;

    vector_dinamico->datos = (int*)calloc(vector_dinamico->tamano, sizeof(int)); 

    for (int i = 0; i < vector_dinamico->tamano; i++ ) { 
            vector_dinamico->datos[i] = temp[i];
    }
    free(temp);

}

// Reducir el tamano del vector a la mitad cuando esté 1/4 o 25% lleno   
void disminuir_vector_dinamico(Vector_Dinamico *vector_dinamico) {

    if ((vector_dinamico->cantidad < vector_dinamico->tamano / 4) && 
        (vector_dinamico->tamaño >= 4)) { 
       
        printf("Disminuyendo el tamano actual del vector a la mitad ( %d / 2 )\n", vector_dinamico->tamano); 
 
        int *temp = vector_dinamico->datos; 
        vector_dinamico->tamano /= 2;
        //vector_dinamico->tamano = vector_dinamico->tamano / 2;

        vector_dinamico->datos = (int*)calloc(vector_dinamico->tamano, sizeof(int)); 

        for (int j = 0; j < vector_dinamico->tamano; j++ ) { 
            vector_dinamico->datos[j] = temp[j];
        }
        free(temp);
    }
}

int busqueda_binaria_iterativa_vector_dinamico(int *datos, int cantidad, int valor) {
    
    int inicio = 0, fin = cantidad - 1, index_medio;

    while (inicio <= fin) { // mientras el vector tenga al menos 1 elemento.

        index_medio = (inicio + fin) / 2;
        if (datos[index_medio] == valor) 
           return index_medio;
        
        else if (datos[index_medio] > valor)
            fin = index_medio - 1;
        
        else 
            inicio = index_medio + 1;
    } 
    return -1;
}    

int busqueda_binaria_recursiva_vector_dinamico(int *datos, int limite_izquierda, int limite_derecha, int valor) {    
    
    int index_medio = (limite_izquierda + limite_derecha) / 2;

    printf("%d\n", index_medio);

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

int busqueda_secuencial_vector_dinamico(Vector_Dinamico *vector_dinamico, int valor) {    
    
    for (int i = 0; i < vector_dinamico->cantidad; i++) {
        if (vector_dinamico->datos[i] == valor) 
            return i; //retorna el indice del elemento.
    }    
    return -1; //caso no encuentre el elemento, retorna -1 con indice.
}

// Interfaces disponibles para nuestros clientes, en este caso quienes usaran nuestro TAD. 
// Estan definidas en nuestro vector_dinamico.h

Vector_Dinamico* crear_vector_dinamico(int tamano_vector, bool ordenado) {

    Vector_Dinamico *vector_dinamico = (Vector_Dinamico*) malloc(sizeof(Vector_Dinamico));
    vector_dinamico->ordenado = ordenado;
    vector_dinamico->cantidad = 0;
    vector_dinamico->tamano = tamaño_vector;
    vector_dinamico->datos = (int*) calloc(tamano_vector, sizeof(int));
    
    return vector_dinamico;

}

void destruir_vector_dinamico(Vector_Dinamico **vector_dinamico_direccion) {

    Vector_Dinamico *vector_dinamico = *vector_dinamico_direccion;
    free(vector_dinamico->datos);
    free(vector_dinamico);
    *vector_dinamico_direccion = NULL;

}

void imprimir_vector_dinamico(const Vector_Dinamico *vector_dinamico) {

    /*printf("indice = { ");       
    for (int i = 0; i < vector_dinamico->cantidad; i++) {
        printf("%i  ", i);
        if (!(i == vector_dinamico->cantidad-1))
            printf(",");
    }    
    printf("\n"); */

    printf("vector(indice = valor) = { ");       
    for (int i = 0; i < vector_dinamico->cantidad; i++) {
        printf("%i = %d ", i, vector_dinamico->datos[i]);
        //printf("%d  ", vector_dinamico->datos[i]); 
        if (!(i == vector_dinamico->cantidad-1))
            printf("| ");
    }
    printf(" } \n\n");
}

void anadir_vector_dinamico(Vector_Dinamico *vector_dinamico, int valor) {

    if (esta_lleno_vector_dinamico(vector_dinamico)) {
               
        aumentar_vector_dinamico(vector_dinamico);
    
    }
    if (vector_dinamico->ordenado) { //encontrar la posicion para insercion, desplazar los elementos hacia la derecha e insertar en la posicion. 

        int i;
        for (i = vector_dinamico->cantidad -1; i >= 0 && vector_dinamico->datos[i] > valor; i--)
            vector_dinamico->datos[i+1] = vector_dinamico->datos[i];
        
        vector_dinamico->datos[i+1] = valor;
        vector_dinamico->cantidad++;

    } else { //inserta en la ultima posicion no ocupada
      
        vector_dinamico->datos[vector_dinamico->cantidad] = valor;
        vector_dinamico->cantidad++;
    }
}

int buscar_vector_dinamico(Vector_Dinamico *vector_dinamico, int valor) { 
    
    int index = -1; //-1 caso no encuentre el valor;
    if (vector_dinamico->ordenado) {

       //index = busqueda_binaria_recursiva_vector_dinamico(vector_dinamico->datos, 0, vector_dinamico->cantidad-1, valor); // retorna el indice del elemento
       index = busqueda_binaria_iterativa_vector_dinamico(vector_dinamico->datos, vector_dinamico->cantidad, valor);

    } else {

       index = busqueda_secuencial_vector_dinamico(vector_dinamico, valor); // retorna el índice del elemento 

    }
    return index;
}

void eliminar_vector_dinamico(Vector_Dinamico *vector_dinamico, int index) { 
   
    if (index >= 0 && index < vector_dinamico->cantidad) { 
      
        if (vector_dinamico->ordenado) { 
            for (int i = index ; i < vector_dinamico->cantidad - 1; i++) {
                vector_dinamico->datos[i] = vector_dinamico->datos[i + 1]; //mueve una posicion todos los elementos mayores que el elemento que fue eliminado
            }
            vector_dinamico->cantidad--; //decrementa la cantidad      
      
        } else {
        
            vector_dinamico->datos[index] = vector_dinamico->datos[vector_dinamico->cantidad - 1]; //mueve el ultimo elemento (cantidad -1) al lugar del elemento que fue eliminado
            vector_dinamico->cantidad--; //decrementa la cantidad     
        }
    
        disminuir_vector_dinamico(vector_dinamico);
    }
}


int acceder_vector_dinamico(const Vector_Dinamico *vector_dinamico, int index) {

    return vector_dinamico->datos[index];
} 

int acceder_verificado_vector_dinamico(const Vector_Dinamico *vector_dinamico, int index) { // verifica si tiene elemento

    if (index >= 0 && index < vector_dinamico->cantidad)
       return vector_dinamico->datos[index];
    return -1;
}

int tamano_vector_dinamico(const Vector_Dinamico *vector_dinamico) {
    return vector_dinamico->tamano;
}

int cantidad_vector_dinamico(const Vector_Dinamico *vector_dinamico) {
    return vector_dinamico->cantidad;
}
