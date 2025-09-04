all: complex_calc                               # Objetivo por defecto: construye el ejecutable 'complex_calc'

complex_calc: main.o complex.o                  # Regla: 'complex_calc' depende de los objetos main.o y complex.o
	gcc main.o complex.o -o complex_calc.out    # Enlace: genera el binario 'complex_calc.out' (Linux/macOS)
# para Windows comentar la línea de arriba y descomentar la de abajo  
#	gcc main.o complex.o -o complex_calc.exe   # Enlace alternativo: genera 'complex_calc.exe' (Windows)

complex.o: complex.c complex.h                  # Regla: 'complex.o' depende de la implementación y el header
	gcc -Wall -Wextra -std=c11 -O2 -c complex.c -o complex.o   # Compilación del módulo complex.c a objeto (sin enlazar)

main.o: main.c complex.h                        # Regla: 'main.o' depende del main y del header público
	gcc -Wall -Wextra -std=c11 -O2 -c main.c -o main.o         # Compilación de main.c a objeto (sin enlazar)

run:                                            # Objetivo de conveniencia: compila (si hace falta) y ejecuta un ejemplo
	./complex_calc.out add 1 2 3 4             # Ejecuta el binario con argumentos de prueba (suma de complejos)
# para Windows comentar la línea de arriba y descomentar la de abajo
#	./complex_calc.exe add 1 2 3 4            

clean:                                          # Limpieza de artefactos intermedios/finales
	rm -f complex_calc.out *.o                 # Elimina el ejecutable .out y todos los .o del directorio actual
# para Windows comentar la línea de arriba y descomentar la de abajo  
#	del complex_calc.exe *.o                  
