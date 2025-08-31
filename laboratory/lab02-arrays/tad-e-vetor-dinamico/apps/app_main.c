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

int buscar_vector_dinamico(Vector_Dinamico *vector_dinamico, int valor); //para vectores ordenados, hacer busqueda binaria

int acceder_vector_dinamico(const Vector_Dinamico *vector_dinamico, int index);
int acceder_verificado_vector_dinamico(const Vector_Dinamico *vector_dinamico, int index); // verifica si tiene elemento en el indice pasado.

void eliminar_vector_dinamico(Vector_Dinamico *vector_dinamico, int index); // necesita ajustar los elementos del vector.

int tamano_vector_dinamico(const Vector_Dinamico *vector_dinamico);
int cantidad_vector_dinamico(const Vector_Dinamico *vector_dinamico);

//============================================
void menu_vector_dinamico() { 
   
   printf("--- CONSTRUIR UN MENU CON LAS OPERACIONES ---\n\n");
  
   int operacion = 1;
  
   while (operacion < 10 && operacion > 0) {
      
      printf("---------------------------------------\n");
      printf("        TAD y VECTORES DINAMICOS        \n");
      printf("---------------------------------------\n");
      printf("1 - Anadir un elemento \n");
      printf("2 - Eliminar un elemento \n");
      printf("3 - Buscar un elemento \n");
      printf("4 - Imprimir elementos \n");
      printf("5 - Tamano \n");
      printf("6 - Cantidad de elementos \n");
      printf("7 - Acceder a un elemento \n");
      printf("8 - Acceder a un elemento verificado \n");
      printf("10 - Salir\n");
      printf("---------------------------------------\n");
      printf("Elija una operacion:  ");
      int numero_parametros = (scanf("%d", &operacion)); // retornan el numero de conversiones realizadas con exito. 
      if (numero_parametros != 1) {
         printf("Problemas en la entrada de datos");
      }   
            
      switch (operacion)       {
      case 1:
         printf("Usted eligio la operacion 01\n");
         break;
      case 2:
         printf("Usted eligio la operacion 02\n");
         break;
      case 10:
         printf("Usted eligio la operacion 10\n");
         break;   
      default:
         break;
      }         
   } 
}

void prueba_vector_no_ordenado() {

   printf("\n--- INICIO PRUEBA VECTOR NO ORDENADO ---\n\n");
   
   Vector_Dinamico *vector_dinamico = crear_vector_dinamico(4, false);

   imprimir_vector_dinamico(vector_dinamico);
   printf("tamano del vector: %d\n", tamano_vector_dinamico(vector_dinamico));
   printf("cantidad: %d \n\n", cantidad_vector_dinamico(vector_dinamico));

   printf("anadidos 16 elementos\n");
   for (int i = 0; i < 16; i++)
      anadir_vector_dinamico(vector_dinamico, i*2);

   imprimir_vector_dinamico(vector_dinamico);

   printf("tamano del vector: %d\n", tamano_vector_dinamico(vector_dinamico));
   printf("cantidad: %d \n\n", cantidad_vector_dinamico(vector_dinamico));

   printf("eliminando el valor 20\n");  

   int index = buscar_vector_dinamico(vector_dinamico, 20); 
   eliminar_vector_dinamico(vector_dinamico, index);
   imprimir_vector_dinamico(vector_dinamico);

   printf("tamano del vector: %d\n", tamano_vector_dinamico(vector_dinamico));
   printf("cantidad: %d \n\n", cantidad_vector_dinamico(vector_dinamico));
  
   printf("eliminando 13 elementos\n");
   for (int index = 3; index < 16; index++)
     eliminar_vector_dinamico(vector_dinamico, index);

   imprimir_vector_dinamico(vector_dinamico);
   
   printf("tamano del vector: %d\n", tamano_vector_dinamico(vector_dinamico));  
   printf("cantidad: %d \n\n", cantidad_vector_dinamico(vector_dinamico));

   destruir_vector_dinamico(&vector_dinamico);

   printf("--- FIN PRUEBA VECTOR NO ORDENADO ---\n\n");

}

void prueba_vector_ordenado() {

   printf("\n--- INICIO VECTOR ORDENADO ---\n\n");

   Vector_Dinamico *vector_dinamico = crear_vector_dinamico(4, true);

   imprimir_vector_dinamico(vector_dinamico);
   printf("tamano del vector: %d\n", tamano_vector_dinamico(vector_dinamico));
   printf("cantidad: %d \n\n", cantidad_vector_dinamico(vector_dinamico));

   anadir_vector_dinamico(vector_dinamico, 13);  
   anadir_vector_dinamico(vector_dinamico, 9);
   
   imprimir_vector_dinamico(vector_dinamico);
   printf("tamano del vector: %d\n", tamano_vector_dinamico(vector_dinamico));
   printf("cantidad: %d \n\n", cantidad_vector_dinamico(vector_dinamico));

   anadir_vector_dinamico(vector_dinamico, 4);
   anadir_vector_dinamico(vector_dinamico, 2);

   imprimir_vector_dinamico(vector_dinamico);
   printf("tamano del vector: %d\n", tamano_vector_dinamico(vector_dinamico));
   printf("cantidad: %d \n\n", cantidad_vector_dinamico(vector_dinamico));

   anadir_vector_dinamico(vector_dinamico, 1);
   anadir_vector_dinamico(vector_dinamico, 10);
   anadir_vector_dinamico(vector_dinamico, 44);
   anadir_vector_dinamico(vector_dinamico, 33);
      
   imprimir_vector_dinamico(vector_dinamico);
   printf("tamano del vector: %d\n", tamano_vector_dinamico(vector_dinamico));
   printf("cantidad: %d \n\n", cantidad_vector_dinamico(vector_dinamico));

   int index = buscar_vector_dinamico(vector_dinamico, 9); 
   printf("indice: %d\n", index);
   eliminar_vector_dinamico(vector_dinamico, index);

   imprimir_vector_dinamico(vector_dinamico);

   index = buscar_vector_dinamico(vector_dinamico, 13); 
   printf("indice: %d\n", index);
   eliminar_vector_dinamico(vector_dinamico, index);

   imprimir_vector_dinamico(vector_dinamico);

   index = buscar_vector_dinamico(vector_dinamico, 9); 
   printf("indice: %d\n", index);
   eliminar_vector_dinamico(vector_dinamico, index);
  
   imprimir_vector_dinamico(vector_dinamico);
   printf("tamano del vector: %d\n", tamano_vector_dinamico(vector_dinamico));
   printf("cantidad: %d \n\n", cantidad_vector_dinamico(vector_dinamico));
 
   destruir_vector_dinamico(&vector_dinamico);

   printf("--- FIN PRUEBA VECTOR ORDENADO ---\n\n");
 
}


int main() { 
    
   printf("\n--- PROBANDO EL TAD - TIPO ABSTRACTO DE DATOS ---\n\n");
    
   //int tamano = 4; //vamos a comenzar con un tamano fijo y luego vamos doblando su tamano.  

   //bool ordenado = false; 
  
   //Vector_Dinamico *vector_dinamico = crear_vector_dinamico(tamano, ordenado);

   //menu_vector_dinamico();

   //vector_dinamico->tamano = 10; //no tiene acceso directo a los datos.
   //vector_dinamico->datos[0] = 50; //no tiene acceso directo a los datos.

   prueba_vector_no_ordenado();
   prueba_vector_ordenado();
   
   return 0;
}
