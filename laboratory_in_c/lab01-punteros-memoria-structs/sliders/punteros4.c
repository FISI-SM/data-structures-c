#include <stdio.h>

char *mensagem[] = {  // Vector inicializado.
			"Archivo no encontrado",
			"Error de lectura",
			"Error de escritura",
			"No es posible crear el archivo"
};

void escreveMensagemDeErro(int num) {
	printf ("%s\n", mensagem[num]);
}


int main(){


	escreveMensagemDeErro(3);

	printf("[0] %p, %p \n", (void*)mensagem[0], (void*)mensagem);
	printf("[1] %p, %p \n", (void*)mensagem[1], (void*)(mensagem+1));
	printf("[2] %p, %p \n", (void*)mensagem[2], (void*)(mensagem+2));
	printf("[3] %p, %p \n", (void*)mensagem[3], (void*)(mensagem+3));

}