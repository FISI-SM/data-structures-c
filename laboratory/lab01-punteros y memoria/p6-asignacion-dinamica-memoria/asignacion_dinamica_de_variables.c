#include <stdio.h>
#include <stdlib.h>  // contiene NULL, calloc, malloc, free


int main() {

    /*
    Asignacion estatica de memoria.    
    Toda variable se aloca en la memoria Stack. 
    El espacio para las variables se asigna al inicio de la ejecucion y cada variable recibe una direccion de memoria que 
    se mantiene hasta el final de la ejecucion, cuando el sistema operativo desaloca automaticamente. 
  
    Asignacion dinamica de memoria
    Se hace en la memoria Heap. 
    La asignacion dinamica de memoria es el proceso que asigna memoria en tiempo de ejecucion.
    Se utiliza cuando no se sabe previamente cuanta memoria sera necesaria para almacenar los datos. 
    Podemos determinar el tamaño de memoria a utilizar conforme a la necesidad, evitando el uso innecesario de memoria.           
   */ 
    
    //asignacion estatica en la (memoria Stack). 
    printf(" --- ASIGNACION ESTATICA --- \n");
    int a = 30; 
    printf("&a = %p, a = %d \n\n", &a, a);


    //asignacion dinamica en la (memoria Heap) con la funcion malloc
    printf(" --- ASIGNACION DINAMICA USANDO LA FUNCION (malloc) --- \n");
    int *b = malloc(1 * sizeof(int)); // malloc no inicializa el espacio asignado. Todos los elementos tienen basura de memoria.
    *b = 20; 
    printf("&b = %p | b = %p | *b = %d \n", &b, b, *b);
    free(b); //desasigna/libera la direccion de la memoria Heap. La funcion free() informa al sistema operativo que nuestro programa ya no usara esa direccion. 
    printf("&b = %p | b = %p | *b = %d \n", &b, b, *b);  
    b = NULL; // buena practica de programacion
    printf("&b = %p | b = %p \n\n", &b, b); // Si intentas acceder al contenido ( *b ) retorna error, porque el puntero b ya no guarda ninguna direccion. 


     //asignacion dinamica en la (memoria Heap) con la funcion calloc
    printf(" --- ASIGNACION DINAMICA USANDO LA FUNCION (calloc) --- \n" );
    int *c = calloc(1, sizeof(int)); // calloc inicializa el espacio asignado.
    *c = 50; 
    printf("&c = %p | c = %p | *c = %d \n", &c, c, *c);
    free(c); //desasigna/libera la direccion de la memoria Heap 
    c = NULL;
    printf("&c = %p | c = %p \n\n", &c, c);
    
    return 0;
}
