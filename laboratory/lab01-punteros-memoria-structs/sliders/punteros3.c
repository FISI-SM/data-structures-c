/**
 * Punteros en Matrices
 * **/

#include <stdio.h>
#include <string.h>

int main(){
	char nome[30] = "Jose da Silva";
	char *p1, *p2;
	char car;
	int i;

	p1 = nome;                      // El nombre es un indicador
	                                // para el 1° elemento de nome[].
	car = nome[3];                  // Asigna 'é' al car.
	car = p1[0];                    // Asigna 'J' al car. Válido.
	p2 = &nome[5];                  // Asigna a p2 la dirección de 6ª
	                             // posición de nome, en este caso 'd'.
	printf("1) %s\n", p2);               // Imprime "da Silva"...

	p2 = p1;                        // Evidentemente válido.
	p2 = p1 + 5;                    // Equivalente a p2 = &nome[5]
	printf("2) %s\n", (p1 + 5));         // Imprime "da Silva"...
	printf("3) %s\n", (p1 + 20));        // Cuidado: imprime basura!!!

	printf("Into to for: \n");

	for(i = 0;i <= strlen(nome)-1;i++) {
		printf("%c", nome[i]);       // Imprime 'J','o','s'...
		p2 = p1 + i;
		printf("%c", *p2);           // Imprime 'J','o','s'...
	}
}