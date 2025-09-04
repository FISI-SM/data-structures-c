#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h> 

//Especificacion de las operaciones de nuestro TAD.
//crear, destruir, añadir, eliminar y buscar son operaciones basicas que podemos realizar en TAD. 

typedef struct vector_dinamico Vector_Dinamico;

Vector_Dinamico* crear_vector_dinamico(int tamano_vector, bool ordenado);
void destruir_vector_dinamico(Vector_Dinamico **vector_dinamico_direccion);

void imprimir_vector_dinamico(const Vector_Dinamico  *vector_dinamico);

void anadir_vector_dinamico(Vector_Dinamico *vector_dinamico, int valor); // si ordenado=true utilizar este metodo

int buscar_vector_dinamico(Vector_Dinamico *vector_dinamico, int valor); //para vectores ordenados, hacer búsqueda binaria

int acceder_vector_dinamico(const Vector_Dinamico *vector_dinamico, int index);
int acceder_verificado_vector_dinamico(const Vector_Dinamico *vector_dinamico, int index); // verifica si tiene elemento en el indice pasado.

void eliminar_vector_dinamico(Vector_Dinamico *vector_dinamico, int index); // necesita ajustar los elementos del vector.

int tamano_vector_dinamico(const Vector_Dinamico *vector_dinamico);
int cantidad_vector_dinamico(const Vector_Dinamico *vector_dinamico);
