#include <stdio.h>

int main() {
   
    /*
    La memoria RAM (Random Access Memory) de cualquier computadora es una secuencia de bytes, 
    donde cada byte almacena 8 bits de información y es una dirección de memoria. 
    Estas direcciones utilizan el sistema hexadecimal.

    Decimal:  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, ..., n - 1.
    Hexadecimal: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F, 10, 11, 12, 13, ..., n - 1.

    Una variable es un espacio o una posición, localizada en la memoria de la computadora capaz de almacenar un valor/contenido. 
    Toda variable tiene un nombre, un tipo de dato, un valor/contenido y una dirección de memoria. 
    Ocupa una cantidad de bytes dependiendo de su tipo de dato.

    Los tipos de datos pueden ser char que ocupa 1 byte, int ocupa 4 bytes, double ocupa 8 bytes, entre otros.

    El operador & antes de la variable devuelve la dirección de memoria de la misma, esa dirección es 
    del primer byte de la secuencia de bytes ocupada por la variable.
    La función sizeof devuelve el número de bytes para un determinado tipo de dato.     
    */   
    
    char a = 'A'; 
    int b = 1;

    printf("&a = %p \n\n", &a);
    printf("&a = %p \n\n", &b);

    printf("&a = %p \n\n", refb);


    unsigned long tamano_a = sizeof(a);
    unsigned long tamano_b = sizeof(b);

    printf("El tamano de la variable ( a ) es %ld bytes\n", sizeof(a));   
    printf("El tamano de la variable ( a ) es %ld bytes\n\n", tamano_a);

    printf("&a = hexa: %p | dec: %ld \n", &a, &a);
    printf("&b = hexa: %p | dec: %ld \n\n", &b, &b);
   
    return 0;
}

/*
printf
%c -> caracter simple (CHAR)
%d -> decimal (INT)
%ld -> entero “largo” (LONG INT)
%f -> punto flotante (FLOAT)
%o -> octal
%s -> cadena de caracteres (STRING)
%x -> hexadecimal
%lf -> double
*/
