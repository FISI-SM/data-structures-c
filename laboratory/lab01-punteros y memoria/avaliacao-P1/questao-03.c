#include <stdio.h>

int funcion_01(int x, int *y) {
      int w = *y;
      *y = x - 1;
      return 11 + w;
}

int main() {

    int a =33, b=10;
    a = funcion_01(a, &b) + 12;
    b++; 
    printf("%d \n", a);
    printf("%d \n", b); 

}
