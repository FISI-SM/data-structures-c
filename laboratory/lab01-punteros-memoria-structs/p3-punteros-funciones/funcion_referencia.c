#include <stdio.h>

//Ejemplo de funciones con paso de parametros por referencia

//void cambio(const int *valor_x, int *valor_y) { la palabra reservada const indica que la variable es solo de lectura.
void cambio(int *valor_x, int *valor_y) {
   
    int valor_a;
    
    printf("### DENTRO DE LA FUNCION ### \n");
    printf("&valor_x = %p | valor_x = %p | *valor_x = %d\n", &valor_x, valor_x, *valor_x);
    printf("&valor_y = %p | valor_y = %p | *valor_y = %d\n", &valor_y, valor_y, *valor_y);
    printf("&valor_a = %p | valor_a = %d \n\n", &valor_a, valor_a); 

    valor_a = *valor_x;
    printf("&valor_a = %p, valor_a = %d\n\n", &valor_a, valor_a); 

    *valor_x = *valor_y;
    *valor_y = valor_a;              
}   

int main() {
    
    /*
    Las funciones son bloques de instrucciones(codigos) que pueden ser nombradas y llamadas en cualquier parte de un programa.
    Toda funcion tiene un nombre, un tipo que determina su valor de retorno y puede o no tener parametros. 
    Tambien no se puede declarar una funcion dentro de otra funcion.    
    */

   int valor_a = 20;
   int valor_b = 30;

   printf("### ANTES DE LLAMAR A LA FUNCION ### \n");
   printf("&valor_a = %p | valor_a = %d\n", &valor_a, valor_a);
   printf("&valor_b = %p | valor_b = %d\n\n", &valor_b, valor_b);

   cambio(&valor_a, &valor_b);

   printf("### DESPUES DE LLAMAR A LA FUNCION ### \n");
   printf("&valor_a = %p | valor_a = %d\n", &valor_a, valor_a);
   printf("&valor_b = %p | valor_b = %d\n\n", &valor_b, valor_b);
    
   return 0;
    
}
