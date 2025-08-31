#include <stdio.h>

int main() {

    int vector[5] = {5, 10, 15, 20, 25};

    int *p = vector;

    //el nombre de un vector es un puntero al primer indice.  
    printf("&vector   = %p \n", &vector);
    printf("vector    = %p \n", vector);
    printf("vector[0] = %p \n", &vector[0]);
    printf("p         = %p \n\n", p);

    printf("*vector  = %d \n", *vector);
    printf("*p       = %d \n\n", *p);

   
    for (int i = 0;i < 5;i++){
       printf("&vector[%d] = %p | vector[%d] = %d \n", i, &vector[i], i, vector[i]);
       printf("p+%d     = %p | p+%d    = %d \n\n", i, p+i, i, *(p + i));
    }

    printf("\n"); 
    
    return 0;
}
