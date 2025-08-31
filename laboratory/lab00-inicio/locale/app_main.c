#include <locale.h>
#include <stdio.h>

int main (void) {
   setlocale (LC_ALL, ""); // importa las variables de entorno, SO
   setlocale (LC_CTYPE, "es_ES.UTF-8"); // por si acaso, set manual
   char buffer[50];
   scanf ("%[^\n]s", buffer); 
   printf ("%s\n", buffer);
   return 0;
}
