#include <stdio.h>

int a1 = 1;
int a2 = 2;
int a3 = 3;

int *vetor[] = {&a1, &a2, &a3};



void imprimeTodos() {
	int i;
	for(i = 0;i < 3;i++)
		printf("%i ,=> %p \n", *vetor[i], vetor[i]);
}

int main(){

	printf("%d => %p\n",a1, (void*)&a1);
	printf("%d => %p\n",a2, (void*)&a2);
	printf("%d => %p\n",a3, (void*)&a3);

	printf("Inside for \n");

	imprimeTodos();
	
}