#include <stdio.h>
#include <stdlib.h>  // contiene NULL, calloc, malloc, free


// const indica que no queremos alterar el contenido del parametro.
void imprimir_vector(const int vector[], int tamano_vector) { // se puede usar de esta forma *vector
    for (int i = 0; i < tamano_vector; i++) {
        printf("&vector[%d] = %p, vector[%d] = %d\n", i, &vector[i], i, vector[i]);
        // vector[i]++ 
    }
    printf("\n");
}

void llenar_vector(int *vector) { // se puede usar de esta forma vector[]
    vector[0] = 30;
    vector[1] = 10;
    vector[2] = 50;
    vector[3] = 20 ;
    vector[4] = 40;  
}

void sumar_vector_con_escalar(int vector[], int tamano_vector, int escalar) { //*vector
    for (int i = 0; i < tamano_vector; i++) {
        vector[i] += escalar;
    }
}

void desalojar_vector(int **direccion_vector) {
    int *vector = *direccion_vector;
    free(vector);
    *direccion_vector = NULL;
}

int main() {

    // Toda variable se aloca en la (memoria Stack). 
    int tamano_vector = 5;

    // asignacion de un vector estatico (memoria Stack). 
    printf(" --- ASIGNACION ESTATICA DE VECTOR --- \n");
    
    //int vector_estatico[tamano_vector] = {30, 10, 50, 20, 40}; 
    int vector_estatico[tamano_vector]; 
    
    llenar_vector(vector_estatico);
    imprimir_vector(vector_estatico, tamano_vector);
    sumar_vector_con_escalar(vector_estatico, tamano_vector, 10);
    imprimir_vector(vector_estatico, tamano_vector);


    // asignacion de un vector dinamico (memoria Heap).  
    printf("\n --- ASIGNACION DINAMICA DE VECTOR --- \n");
    int *vector_dinamico = (int *) malloc(tamano_vector * sizeof(int));
    
    llenar_vector(vector_dinamico);
    imprimir_vector(vector_dinamico, tamano_vector);
    sumar_vector_con_escalar(vector_dinamico, tamano_vector, 10);
    imprimir_vector(vector_dinamico, tamano_vector);

    printf("\n --- ANTES DE DESALOJAR VECTOR DINAMICO --- \n");
    printf("&vector_dinamico = %p, vector_dinamico = %p\n\n", &vector_dinamico, vector_dinamico);
    
    //free(vector_dinamico);
    // vector_dinamico = NULL;
    desalojar_vector(&vector_dinamico);

    printf("\n --- DESPUES DE DESALOJAR VECTOR DINAMICO --- \n");
    printf("&vector_dinamico = %p, vector_dinamico = %p\n\n", &vector_dinamico, vector_dinamico);

    return 0;
}
