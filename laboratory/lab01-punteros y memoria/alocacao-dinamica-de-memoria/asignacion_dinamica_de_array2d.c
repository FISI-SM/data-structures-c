#include <stdio.h>
#include <stdlib.h>

void matriz2d(int a, int b) {

    int** matriz;

    int filas = a;
    int columnas = b;

    matriz = (int**) malloc(sizeof(int*) * filas);

    for(int i = 0; i < filas; i++) {
        matriz[i] = (int*) malloc(sizeof(int) * columnas);
    }
    
    int cont = 1;
    for (int i=0; i<filas; i++) {
       for (int j=0; j<columnas; j++) {
          matriz[i][j] = cont; 
          cont++; 
       }
    }

   printf("{ \n");
   for (int i=0; i<filas; i++) {
      printf("   { ");
      for (int j=0; j<columnas; j++) {
          printf("%d ", matriz[i][j]);        
      }      
       printf("} \n");
    }
    printf("} \n\n");  

//    matriz[2][3] = 10;

    for (int i=0 ; i<filas ; i++ ){
        free (matriz[i]);
    }
    free ( matriz );
}

int main() {  
  
    matriz2d(3, 4);  
   
    return 0;
}
