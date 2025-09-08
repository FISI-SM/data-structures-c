#include <stdio.h>
#include <string.h>
#include <stdlib.h>  // contiene NULL, calloc, malloc, free

int main() {
   
   typedef struct persona {
        char nombre[30];
        int edad;
   } Persona;  
    
   printf(" --- ASIGNACION ESTATICA DE ESTRUCTURA --- \n");
   Persona persona_estatica; 

   strcpy(persona_estatica.nombre, "Ederson Schmeing");
   persona_estatica.edad = 38;

   printf("Nombre: %s \n", persona_estatica.nombre);
   printf("Edad: %d \n\n", persona_estatica.edad);


   printf(" --- ASIGNACION DINAMICA DE ESTRUCTURA --- \n");
   Persona *persona_dinamica = (Persona*) malloc(1 * sizeof(Persona));

   strcpy(persona_dinamica->nombre, "Ederson");
   persona_dinamica->edad = 3;

   printf("Nombre: %s \n", persona_dinamica->nombre);
   printf("Edad: %d \n\n", persona_dinamica->edad);

   strcpy((*persona_dinamica).nombre, "Schmeing");
   (*persona_dinamica).edad = 8;

   printf("Nombre: %s \n", (*persona_dinamica).nombre);
   printf("Edad: %d \n\n",(*persona_dinamica).edad);

   free(persona_dinamica);
   persona_dinamica = NULL;
 
   return 0;
}
