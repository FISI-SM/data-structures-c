#include <stdio.h>
#include <stdlib.h>


void matriz3d(int a, int b, int c ) { 

    int*** matriz;

    int filas = a;
    int columnas = b;
    int profundidades = c;

    matriz = (int***) malloc(sizeof(int**) * filas);

    for(int i=0; i<filas; i++) {
        matriz[i] = (int**) malloc(sizeof(int*) * columnas);
    }

    for ( int i=0; i<filas; i++){ 
       for (int j=0 ; j<columnas; j++){ 
            matriz[i][j] = (int*) malloc (sizeof (int) * profundidades);
        }   
    }

    int cont = 1;
    for (int i=0; i<filas; i++) {
       for (int j=0; j<columnas; j++) {
          for (int k=0; k<profundidades; k++) {
             matriz[i][j][k] = cont;
             cont++;
          }
       }
    } 

    //matriz[0][0][0] = 250;
    //matriz[1][1][1] = 333;
    //matriz[2][2][2] = 555; 

    //printf("%d ", matriz[0][0][0]);  
    //printf("%d ", matriz[1][1][1]);
    //printf("%d ", matriz[0][2][0]); 

    printf("{ \n");
    for (int i=0; i<filas; i++) {
        printf("   { \n");
        for (int j=0; j<columnas; j++) {
            printf("      { ");
           for (int k=0; k<profundidades; k++) {
              printf("%d ", matriz[i][j][k]);        
           }
           printf("} \n");
        }      
        printf("   } \n");
     }
     printf("} \n\n");  

  // inicio liberación de la matriz
    for (int i=0 ; i<filas ; i++){
        for (int j=0; j<columnas ; j++){
            free ( matriz[i][j] );
        }
    } 
   for (int i=0; i<filas; i++){
        free (matriz[i]);
    }
    free (matriz);
}

int main() {  
    matriz3d(4, 3, 2);
    return 0;
}
