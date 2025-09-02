#include "lista_enlazada_circular.h" 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>  

struct nodo {
    int datos; 
    Nodo *siguiente;  
};

Nodo *crear_lista() {
   return NULL;
}

void destruir_lista_enlazada(Nodo **ptr_ptr_nodo) {
 
    Nodo *ptr_nodo_ultimo = *ptr_ptr_nodo;
    
    if (ptr_nodo_ultimo == NULL) { // lista vacia 
       return; 
    }

    Nodo *ptr_nodo_actual = ptr_nodo_ultimo->siguiente; //inicio de la lista
    Nodo *ptr_nodo_auxiliar;       

    //  printf("%p \n", ptr_nodo_actual);
   
    while (ptr_nodo_actual != ptr_nodo_ultimo) {
        ptr_nodo_auxiliar = ptr_nodo_actual;
        ptr_nodo_actual = ptr_nodo_actual->siguiente; 
        free(ptr_nodo_auxiliar);
    }

    free(*ptr_ptr_nodo); 
    //    free(ptr_nodo_actual);
    printf("%d \n", (*ptr_ptr_nodo)->datos);
    *ptr_ptr_nodo = NULL;
    printf("%p \n", *ptr_ptr_nodo);
    
}

void imprimir_lista(Nodo *ptr_nodo) { 
   
   Nodo *ptr_nodo_ultimo = ptr_nodo;
   Nodo *ptr_nodo_actual;
   
   if (ptr_nodo != NULL) {

      for (ptr_nodo_actual = ptr_nodo->siguiente;
           ptr_nodo_actual != ptr_nodo_ultimo;
           ptr_nodo_actual = ptr_nodo_actual->siguiente) {

         printf("%d -> ", ptr_nodo_actual->datos);   
      }
      printf("%d -> \n", ptr_nodo_actual->datos);  

   } else { 

      printf("NULL\n");
   
   }
 
}

int tamaño_lista(const Nodo *ptr_nodo) { 
    
    //TODO: Implementa esta funcion.
    return 0;

}

/*

**ptr_ptr_nodo es un puntero de puntero para la estructura NODO, 
almacena la direccion de memoria de la variable del tipo puntero 
a NODO que esta en la pila y almacena la direccion de memoria 
del ultimo nodo/elemento de la lista. 

**ptr_ptr_nodo = &lista;

*/

void agregar_inicio_lista(Nodo **ptr_ptr_nodo, int valor) {  //&l

    Nodo *ptr_nodo_nuevo = (Nodo*) malloc(sizeof(Nodo));
    ptr_nodo_nuevo->datos = valor;
   
    if (*ptr_ptr_nodo == NULL) { // lista vacía
       *ptr_ptr_nodo = ptr_nodo_nuevo;
       ptr_nodo_nuevo->siguiente = ptr_nodo_nuevo; 
       
    } else {

       ptr_nodo_nuevo->siguiente = (*ptr_ptr_nodo)->siguiente;
       (*ptr_ptr_nodo)->siguiente = ptr_nodo_nuevo;   

    }
    
} 

/*

**ptr_ptr_nodo es un puntero de puntero para la estructura NODO, 
almacena la direccion de memoria de la variable del tipo puntero 
a NODO que está en la pila y almacena la direccion de memoria 
del ultimo nodo/elemento de la lista. 

**ptr_ptr_nodo = &lista;

*/
void agregar_final_lista(Nodo **ptr_ptr_nodo, int valor) { 

    Nodo *ptr_nodo_nuevo = (Nodo*) malloc(sizeof(Nodo));
    ptr_nodo_nuevo->datos = valor;
    
    if (*ptr_ptr_nodo == NULL) { //lista vacia
       *ptr_ptr_nodo = ptr_nodo_nuevo;
       ptr_nodo_nuevo->siguiente = ptr_nodo_nuevo; 
    
    } else {

       ptr_nodo_nuevo->siguiente = (*ptr_ptr_nodo)->siguiente;
       (*ptr_ptr_nodo)->siguiente = ptr_nodo_nuevo;  
       *ptr_ptr_nodo = ptr_nodo_nuevo;       
   
    }
} 

// se puede dejar para implementar al final 
void agregar_ordenado_lista(Nodo **ptr_ptr_nodo, int valor) {

     //TODO: Implementa esta funcion.

} 

bool eliminar_inicio_lista(Nodo **ptr_ptr_nodo) {
 
     //TODO: Implementa esta funcion.
     return 1;

} 

bool eliminar_final_lista(Nodo **ptr_ptr_nodo) {
    
   if (*ptr_ptr_nodo == NULL) //lista vacia
       return false;

   Nodo *ptr_nodo_ultimo = *ptr_ptr_nodo;

   if (ptr_nodo_ultimo->siguiente == *ptr_ptr_nodo) { // un nodo/elemento 
      free(ptr_nodo_ultimo);
      *ptr_ptr_nodo = NULL;
      return true;
   } 

   Nodo *ptr_nodo_actual = ptr_nodo_ultimo;

   while (ptr_nodo_actual->siguiente != ptr_nodo_ultimo ) {
      ptr_nodo_actual =  ptr_nodo_actual->siguiente;  
   }
   ptr_nodo_actual->siguiente = ptr_nodo_ultimo->siguiente;
   *ptr_ptr_nodo = ptr_nodo_actual;

   return true;

} 

bool eliminar_valor_lista(Nodo **ptr_ptr_nodo, int valor) { 

   //TODO: Implementa esta funcion.
   return true;   

} 

int buscar_valor_lista(Nodo *ptr_ptr_nodo, int valor) {  // puede retornar la posicion o el propio valor, si los datos fueran un tipo compuesto retornariamos el
   
   //TODO: Implementa esta funcion.
   return -1;

}

int buscar_posicion_lista(Nodo *ptr_ptr_nodo, int posicion) { //retornar el valor de la posicion
   
   //TODO: Implementa esta funcion.
   return -1;

}
