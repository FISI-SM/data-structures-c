#include "circunferencia.h"
#include <stdio.h>
#include <math.h>

Punto crear_punto(double x, double y){
	Punto temp;
	temp.x = x;
	temp.y = y;

	return temp;
}

Circun crear_circunferencia(Punto centro, double r){
	Circun temp;
	temp.centro = centro;
	temp.radio = r;

	return temp;
}

// return 0: No pertenece; 1 caso contrario
int verificar_pertenece(Circun c, Punto p){
	//(x - X)^2 + (y - Y)^2 = r^2
	double val = (c.centro.x - p.x)*(c.centro.x - p.x) + 
					(c.centro.y - p.y)*(c.centro.y - p.y);
	if(val <= c.radio*c.radio)
		return 1;
	
	return 0;						
}








