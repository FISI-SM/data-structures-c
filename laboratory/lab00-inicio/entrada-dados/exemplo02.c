#include <stdio.h>
#include <stdlib.h>


char *leer_texto() { 

    char *texto = NULL;
    char caracter_actual;
    int tamanio_texto = 0;

    do {

         scanf("%c", &caracter_atual);
         tamanio_texto++;
         texto = (char*) realloc(texto, tamanio_texto * sizeof(char));
        
         if (caracter_actual != '\n')
            texto[tamanio_texto-1] = caracter_actual;
         else 
            texto[tamanio_texto-1] = '\0';

    } while (caracter_actual != '\n');
    

    return texto;
}


int main() {
    
    char *texto;
    int tamanio_texto;

    texto = leer_texto();

    printf("\n%s\n", texto);

    return 0;
}
