#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int M = 0;

struct alumno{
    int matricula;
    char nombre[30];
    float n1, n2, n3;
};

void printfVet(int *V, int N){
    int i;
    for(i = 0; i < N; i++)
        printf("%2d ",V[i]);
    printf("\n");
}

//============================================

void bubbleSort(int *V, int N){
    int i, continua, aux;
    do{
        continua = 0;
        for(i = 0; i < N-1; i++){
            if (V[i] > V[i+1]){
                aux = V[i];
                V[i] = V[i+1];
                V[i+1] = aux;
                continua = 1;
            }
        }
    }while(continua);
}

void bubbleSort2(int *V, int N){//optimizado
    int i, continua, aux, fin = N;
    do{
        continua = 0;
        for(i = 0; i < fin-1; i++){
            if (V[i] > V[i+1]){
                aux = V[i];
                V[i] = V[i+1];
                V[i+1] = aux;
                continua = i;
            }
        }
        fin--;
    }while(continua != 0);
}
//============================================
void insertionSort(int *V, int N){
    int i, j, aux;
    for(i = 1; i < N; i++){
        aux = V[i];
        for(j = i; (j > 0) && (aux < V[j - 1]); j--)
            V[j] = V[j - 1];
        V[j] = aux;
    }
}
//============================================
void selectionSort(int *V, int N){
    int i, j, menor, intercambio;
    for(i = 0; i < N-1; i++){
        menor = i;
        for(j = i+1; j < N; j++){
            if(V[j] < V[menor])
                menor = j;
        }
        if(i != menor){
            intercambio = V[i];
            V[i] = V[menor];
            V[menor] = intercambio;
        }
    }
}
//============================================
void merge(int *V, int inicio, int medio, int fin){
    int *temp, p1, p2, tamano, i, j, k;
    int fin1 = 0, fin2 = 0;
    tamano = fin-inicio+1;
    p1 = inicio;
    p2 = medio+1;
    temp = (int *) malloc(tamano*sizeof(int));
    if(temp != NULL){
        for(i=0; i<tamano; i++){
            if(!fin1 && !fin2){
                if(V[p1] < V[p2])
                    temp[i]=V[p1++];
                else
                    temp[i]=V[p2++];

                if(p1>medio) fin1=1;
                if(p2>fin) fin2=1;
            }else{
                if(!fin1)
                    temp[i]=V[p1++];
                else
                    temp[i]=V[p2++];
            }
        }
        for(j=0, k=inicio; j<tamano; j++, k++)
            V[k]=temp[j];
    }
    free(temp);
}

void mergeSort(int *V, int inicio, int fin){
    int medio;
    if(inicio < fin){
        medio = floor((inicio+fin)/2);
        mergeSort(V,inicio,medio);
        mergeSort(V,medio+1,fin);
        merge(V,inicio,medio,fin);
    }
}

//============================================

void insertionSortMatricula(struct alumno *V, int N){
    int i, j;
    struct alumno aux;
    for(i = 1; i < N; i++){
        aux = V[i];
        for(j=i;(j>0) && (aux.matricula<V[j-1].matricula);j--)
            V[j] = V[j - 1];
        V[j] = aux;
    }
}
/*salida strcmp(str1,str2)
    == 0: str1 es igual a str2
     > 0: str1 viene despues de str2
     < 0: str1 viene antes de str2
*/
void insertionSortNombre(struct alumno *V, int N){
    int i, j;
    struct alumno aux;
    for(i = 1; i < N; i++){
        aux = V[i];
        for(j=i;(j>0) && (strcmp(aux.nombre, V[j-1].nombre) < 0);j--)
            V[j] = V[j-1];
        V[j] = aux;
    }
}

//============================================


int main(){
    int i;

    struct alumno V[4] = {{2,"Andre",9.5,7.8,8.5},
                         {4,"Ricardo",7.5,8.7,6.8},
                         {1,"Bianca",9.7,6.7,8.4},
                         {3,"Ana",5.7,6.1,7.4}};

    insertionSortMatricula(V,4);
    insertionSortNombre(V,4);
    for(i = 0; i < 4; i++)
        printf("%d) %s\n", (V[i]).matricula, V[i].nombre);

    return 0;
}


//==============================================================================

//    int vet[10] = {23,4,67,-8,54,90,21,14,-5,1};
//    int N = 10;

  //  int vet[7] = {23,4,67,-8,90,54,21};
  //  int N = 7;

//    int vet[7] = {23,4,67,-8,21};
//    int N = 5;

 //   printf("Sin ordenar:\n");

    //bubbleSort(vet,N);//OK
