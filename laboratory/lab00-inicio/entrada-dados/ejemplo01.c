#include <stdio.h>

int main() {

    char texto[256];
     
    //[^\n] mascara, tambien conocida como expresion regular.

    scanf("%[^\n]s", texto);

    printf("\n%s\n", texto);

}
