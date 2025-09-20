#include <stdio.h>

int main() {

    typedef struct fecha {
        int dia;
        int mes;
        int anio;    
    } Fecha;
    
    Fecha fecha_actual; 
    
    fecha_actual.dia = 6;
    fecha_actual.mes = 3;
    fecha_actual.anio = 2023; 

    printf("La fecha actual es %d/%d/%d \n\n", fecha_actual.dia, fecha_actual.mes, fecha_actual.anio);

    Fecha *p = NULL; 
    
    p = &fecha_actual;

    p->dia = 10;
    p->mes = 04; 
    p->anio = 2024;

    printf("La fecha actual es %d/%d/%d \n\n", p->dia, p->mes, p->anio);

    (*p).dia = 20; 
    (*p).mes = 05;
    (*p).anio = 2025;

    printf("La fecha actual es %d/%d/%d \n\n", (*p).dia, (*p).mes, (*p).anio);

}
