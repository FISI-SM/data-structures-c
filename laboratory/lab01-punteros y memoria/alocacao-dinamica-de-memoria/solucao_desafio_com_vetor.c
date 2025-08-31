#include <stdio.h>
#include <stdlib.h>  // contiene NULL, calloc, malloc, free

//const indica que no queremos alterar el contenido del parámetro.
void imprimir_vector(const int vector[], int tamano_vector) { // puede ser usado de esta forma *vector
    for (int i = 0; i < tamano_vector; i++) {
        printf("&vector[%d] = %p, vector[%d] = %d\n", i, &vector[i], i, vector[i]);
        // vector[i]++ 
    }
    printf("\n");
}

void llenar_vector(int vector[], int tamano_vector) {
    int elemento;
    for (int i = 0; i < tamano_vector; i++) {
        printf("Ingrese el elemento numero %d: ", i+1);
        //scanf("%d", &vector[i]);
        scanf("%d", &elemento);
        vector[i] = elemento;
    }
}

void multiplica_vector_con_escalar(int vector[], int tamano_vector, int escalar) { //*vector
    for (int i = 0; i < tamano_vector; i++) {
        vector[i] *= escalar;
    }
}

void desalojar_vector(int **direccion_vector) {
    int *vector = *direccion_vector;
    free(vector);
    *direccion_vector = NULL;
}

int main() {

    int tamano_vector;
    int numero_escalar;

    printf("\n --- MULTIPLICACION DE ESCALAR POR VECTOR --- \n");

    printf("Ingrese la cantidad de elementos: ");
    scanf("%d", &tamano_vector);
     
    printf("Ingrese el numero escalar para hacer la multiplicacion: ");
    scanf("%d", &numero_escalar);

    int *vector_dinamico = (int *) malloc(tamano_vector * sizeof(int));

    llenar_vector(vector_dinamico, tamano_vector);
    printf("\n --- ELEMENTOS INFORMADOS --- \n");
    imprimir_vector(vector_dinamico, tamano_vector);
    
    multiplica_vector_con_escalar(vector_dinamico, tamano_vector, numero_escalar);
    printf("\n --- ELEMENTOS DESPUES DE LA OPERACION --- \n");
    imprimir_vector(vector_dinamico, tamano_vector);
 
    //free(vector_dinamico);
    desalojar_vector(&vector_dinamico);
 
    return 0;
}
