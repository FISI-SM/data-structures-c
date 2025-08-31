#include <stdio.h>
#include <string.h>
#include <stdlib.h>  // contiene NULL, calloc, malloc, free

int main() {
   
   typedef struct persona {
        char nombre[30];
        int edad;
   } Persona, *Persona_Ptr;  

   printf(" --- ASIGNACION DINAMICA DE PUNTERO DE PUNTERO DE ESTRUCTURA--- \n");
 

   //Persona *persona_dinamica = (Persona*) malloc(1 * sizeof(Persona*));
   Persona_Ptr persona_dinamica = (Persona_Ptr) malloc(1 * sizeof(Persona_Ptr));
   Persona_Ptr persona_dinamica1 = (Persona_Ptr) malloc(1 * sizeof(Persona_Ptr));
   Persona_Ptr persona_dinamica2 = (Persona_Ptr) malloc(1 * sizeof(Persona_Ptr));

   strcpy(persona_dinamica->nombre, "Ederson Schmeing");
   persona_dinamica->edad = 38;

   strcpy(persona_dinamica1->nombre, "Anderson");
   persona_dinamica1->edad = 41;

   strcpy(persona_dinamica2->nombre, "Isabela");
   persona_dinamica2->edad = 37;
  
   //ASIGNA UN VECTOR DE PUNTEROS DE ESTRUCTURA EN EL MONTON
   Persona_Ptr *vector = (Persona_Ptr*) malloc(10 * sizeof(Persona_Ptr));     

   vector[0] = persona_dinamica;
   vector[1] = persona_dinamica1;
   *(vector + 2) = persona_dinamica2;
   //vector[2] = persona_dinamica2;


   for (int i = 0; i < 10; i++ ) {
      printf("&vector = %p | direccion de struct = %ld | direccion de struct = %p \n", &vector, &vector[i], vector[i]);  
   }

   Persona *persona_0 = vector[0];
   Persona *persona_1 = vector[1];
   Persona *persona_2 = vector[2];

 //De esta forma el vector está en la pila y la estructura en el montón.
   Persona *v[10];
   v[0] = persona_dinamica;
   

   //DESASIGNA MEMORIA
   free(persona_dinamica);
   persona_dinamica = NULL;
   
   free(persona_dinamica1);
   persona_dinamica1 = NULL;
   
   free(persona_dinamica2);
   persona_dinamica2 = NULL;
   
   free(vector); 
   vector = NULL;
   
   //PROBAR SIN COMENTARIO. 
   //Persona *p = vector[0]; */
   
   return 0;

}
