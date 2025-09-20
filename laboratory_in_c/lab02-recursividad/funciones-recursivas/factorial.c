#include <stdio.h>

int factorial(int valor){
    
    if(valor == 1){
        return 1;
    }

    printf("%d * ", valor);
    int fat = factorial(valor - 1); 
    int resultado = valor * fat; 
    return resultado;  
}

// 5 * 4 * 3 * 2 * 1 => 5! es : 120

int main() {
    
    int valor = 5;

    //printf("Ingrese un valor: ");
    //scanf("%d", &valor);
    
    int resultado = factorial(valor);
    printf("1 => ");
    printf("%d! es : %d\n", valor, resultado);
    return 0;
    
}
