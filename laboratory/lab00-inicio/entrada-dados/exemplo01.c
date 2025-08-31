#include <stdio.h>

int main() {

    char texto[256];
     
    //[^\n] mascara, también conocida como expresióo regular.

    scanf("%[^\n]s", texto);

    printf("\n%s\n", texto);

}
