#include <stdio.h>

void intercambio(int, int);       // prototipo

int main(){
	int a=1,b=2; 
   	printf("a=%d b=%d\n",a,b);
	intercambio(a,b);              // llamada
   	printf("a=%d b=%d\n",a,b);
	
	return 0;
}

void intercambio(int x, int y){   // declaración formal
	int temp;
	temp=x; 
	x=y; 
	y=temp; 
	printf(" x=%d y=%d\n",x,y);
}
