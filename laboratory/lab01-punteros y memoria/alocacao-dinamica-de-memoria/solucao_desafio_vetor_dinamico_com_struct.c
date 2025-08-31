#include <stdio.h>
#include <stdlib.h>  // contiene NULL, calloc, malloc, free

typedef struct persona {
    char nombre[30];
    int edad;
} Persona; 

void imprimir_vector(Persona **vector, int tamano_vector)  { 
    for (int i = 0; i < tamano_vector; i++) {
        printf("&vector[%d] = %p, vector[%d].nombre = %s\n", i, &vector[i], i, vector[i]->nombre);
        printf("&vector[%d] = %p, vector[%d].edad = %d\n", i, &vector[i], i, vector[i]->edad);
        printf("\n");
    }
    printf("\n");
}

Persona* crear_persona(char nombre[30], int edad) {
    Persona *persona_dinamica = (Persona*) malloc(1 * sizeof(Persona));
    strcpy(persona_dinamica->nombre, nombre);
    persona_dinamica->edad = edad;
    return persona_dinamica;
}

void llenar_vector(Persona **vector, int tamano_vector) {
    int edad;
    char nombre[30];
    for (int i = 0; i < tamano_vector; i++) {
        printf("Ingrese el nombre de la persona %d: ", i + 1);
        scanf("%s", &nombre);
        
        printf("Ingrese la edad de la persona %d: ", i + 1);
        scanf("%d", &edad);
        
        Persona *persona_dinamica = crear_persona(nombre, edad); 
        vector[i] = persona_dinamica;
    }
}

Persona** crear_vector_dinamico(int tamano_vector) {
  Persona **vector = (Persona**) malloc(tamano_vector * sizeof(Persona*));
  return vector;
}

void desalojar_vector(Persona*** direccion_vector, int tamano_vector) {  
    Persona** vector = *direccion_vector;
    for (int i = 0; i < tamano_vector; i++) {
        free(vector[i]);
        vector[i] = NULL;
    }
    free(vector);
    *direccion_vector = NULL;
}

int main() {

    int tamano_vector;

    printf("\n --- VECTOR DE PUNTEROS A ESTRUCTURAS --- \n");

    printf("Informe la cantidad de elementos: ");
    scanf("%d", &tamano_vector);
      
    Persona** vector = crear_vector_dinamico(tamano_vector);

    llenar_vector(vector, tamano_vector);

    printf("\n --- PERSONAS REGISTRADAS --- \n");
    imprimir_vector(vector, tamano_vector);
    
    desalojar_vector(&vector, tamano_vector);

    return 0;
}
