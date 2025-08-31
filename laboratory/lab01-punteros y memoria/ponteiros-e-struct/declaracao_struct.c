#include <stdio.h>
#include <string.h>

int main() {

   /*
   Una struct es una variable especial que contiene diversas otras variables normalmente de tipos diferentes denominadas miembros.
   Una struct es asignada en una secuencia ordenada en la memoria. 
   */ 

   struct direccion {
        char calle[30];
        int numero;  
   };  
   typedef struct direccion Direccion; 
      
   typedef struct persona {
        char nombre[30];
        int edad;
        struct direccion direccion1;
        Direccion direccion2;
   } Persona;  
   
   Persona p; 

   strcpy(p.nombre, "Ederson Schmeing");
   p.edad = 38;
   strcpy(p.direccion1.calle, "Calle Apalais");
   p.direccion1.numero = 1413;

   strcpy(p.direccion2.calle, "Calle Tito Muffato");
   p.direccion2.numero = 2317 ;

   printf("Nombre: %s \n", p.nombre);
   printf("Edad: %d \n", p.edad);
   printf("Calle Direccion 1: %s \n", p.direccion1.calle);
   printf("Numero Direccion 1: %d \n", p.direccion1.numero);
   printf("Calle Direccion 2: %s \n", p.direccion2.calle);
   printf("Numero Direccion 2: %d \n\n", p.direccion2.numero);   
   
   return 0;

}
