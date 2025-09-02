all: app_main

app_main: app_main.o lista_enlazada_con_cabeza.o  
	gcc obj/app_main.o obj/lista_enlazada_con_cabeza.o -o bin/app_main.out	
# para Windows comenta la linea de arriba y descomenta la linea de abajo
#gcc obj/app_main.o obj/lista_enlazada.o -o bin/app_main.exe	


lista_enlazada_con_cabeza.o: src/lista_enlazada_con_cabeza.c include/lista_enlazada_con_cabeza.h
	gcc -I include -Wall -Werror -c src/lista_enlazada_con_cabeza.c -o obj/lista_enlazada_con_cabeza.o

app_main.o: apps/app_main.c include/lista_enlazada_con_cabeza.h
	gcc -I include -Wall -Werror -c apps/app_main.c -o obj/app_main.o

run:
	./bin/app_main.out
# para Windows comenta la linea de arriba y descomenta la linea de abajo
#./bin/app_main.exe

clean:
	rm -f bin/app_main.out obj/*.o
# para Windows comenta la linea de arriba y descomenta la linea de abajo
#del bin\app_main.exe obj\*.o
