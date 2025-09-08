#include <stdio.h>

int main() {

    typedef struct direccion {
        int *p1;
        int *p2;
    } Direccion;
    


    Direccion direccion;

    int titta = sizeof(direccion);
    printf("GOKU: %d\n", titta);

    int a = 10; 
    int b = 20;

    direccion.p1 = &a;
    direccion.p2 = &b;

    printf("&p1 = %p || p1 = %p || *p1 = %d \n", &direccion.p1, direccion.p1, *direccion.p1);
    printf("&p2 = %p || p2 = %p || *p2 = %d \n\n", &direccion.p2, direccion.p2, *direccion.p2);    

}
