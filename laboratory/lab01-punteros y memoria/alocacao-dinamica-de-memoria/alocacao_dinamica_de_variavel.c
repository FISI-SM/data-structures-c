#include <stdio.h>
#include <stdlib.h>  // contiene NULL, calloc, malloc, free


int main() {

    /*
    Asignación estática de memoria.    
    Toda variable se aloca en la memoria Stack. 
    El espacio para las variables se asigna al inicio de la ejecución y cada variable recibe una dirección de memoria que 
    se mantiene hasta el final de la ejecución, cuando el sistema operativo desaloca automáticamente. 
  
    Asignación dinámica de memoria
    Se hace en la memoria Heap. 
    La asignación dinámica de memoria es el proceso que asigna memoria en tiempo de ejecución.
    Se utiliza cuando no se sabe previamente cuánta memoria será necesaria para almacenar los datos. 
    Podemos determinar el tamaño de memoria a utilizar conforme a la necesidad, evitando el uso innecesario de memoria.           
   */ 
    
    //asignación estática en la (memoria Stack). 
    printf(" --- ASIGNACION ESTATICA --- \n");
    int a = 30; 
    printf("&a = %p, a = %d \n\n", &a, a);


    //asignación dinámica en la (memoria Heap) con la función malloc
    printf(" --- ASIGNACION DINAMICA USANDO LA FUNCION (malloc) --- \n");
    int *b = malloc(1 * sizeof(int)); // malloc no inicializa el espacio asignado. Todos los elementos tienen basura de memoria.
    *b = 20; 
    printf("&b = %p | b = %p | *b = %d \n", &b, b, *b);
    free(b); //desasigna/libera la dirección de la memoria Heap. La función free() informa al sistema operativo que nuestro programa ya no usará esa dirección. 
    printf("&b = %p | b = %p | *b = %d \n", &b, b, *b);  
    b = NULL; // buena práctica de programación
    printf("&b = %p | b = %p \n\n", &b, b); // Si intentas acceder al contenido ( *b ) retorna error, porque el puntero b ya no guarda ninguna dirección. 


     //asignación dinámica en la (memoria Heap) con la función calloc
    printf(" --- ASIGNACION DINAMICA USANDO LA FUNCION (calloc) --- \n" );
    int *c = calloc(1, sizeof(int)); // calloc inicializa el espacio asignado.
    *c = 50; 
    printf("&c = %p | c = %p | *c = %d \n", &c, c, *c);
    free(c); //desasigna/libera la dirección de la memoria Heap 
    c = NULL;
    printf("&c = %p | c = %p \n\n", &c, c);
    
    return 0;
}
