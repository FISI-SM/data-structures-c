#include <stdio.h>

//Ejemplo de funciones con paso de parametros por valor 

int suma_escalar(int valor_x, int valor_y) {
    int suma = valor_x + valor_y;
     
    printf("--- DENTRO DE LA FUNCION --- \n");
    printf("&valor_x = %p | valor_x = %d\n", &valor_x, valor_x);
    printf("&valor_y = %p | valor_y = %d\n", &valor_y, valor_y);
    printf("&suma    = %p | suma    = %d\n\n", &suma, suma); 

    return suma;
}

int main() {
    
    /*
    Las funciones son bloques de instrucciones(codigos) que pueden ser nombradas y llamadas en cualquier parte de un programa.
    Toda funcion tiene un nombre, un tipo que determina su valor de retorno y puede o no tener parametros. 
    Tambien no se puede declarar una funcion dentro de otra funcion.    
    */

    int valor_a = 20;
    int valor_b = 30;
    int resultado;
    
    printf("--- ANTES DE LLAMAR A LA FUNCION --- \n");
    printf("&valor_a   = %p | valor_a   = %d\n", &valor_a, valor_a);
    printf("&valor_b   = %p | valor_b   = %d\n", &valor_b, valor_b);
    printf("&resultado = %p | resultado = %d\n\n", &resultado, resultado);

    resultado = suma_escalar(valor_a, valor_b);

    printf("--- DESPUES DE LLAMAR A LA FUNCIÓN --- \n");
    printf("&valor_a   = %p | valor_a = %d\n", &valor_a, valor_a);
    printf("&valor_b   = %p | valor_b = %d\n", &valor_b, valor_b);
    printf("&resultado = %p | valor_c = %d\n\n", &resultado, resultado);
    
    return 0;
}
