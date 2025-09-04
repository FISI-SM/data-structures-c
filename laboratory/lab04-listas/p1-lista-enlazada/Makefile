all: app_main

app_main: app_main.o lista_enlazada.o  
	gcc obj/app_main.o obj/lista_enlazada.o -o bin/app_main.out	
# para Windows comenta la linea de arriba y descomenta la linea de abajo
#gcc obj/app_main.o obj/lista_enlazada.o -o bin/app_main.exe	

lista_enlazada.o: src/lista_enlazada.c include/lista_enlazada.h
	gcc -I include -Wall -Werror -c src/lista_enlazada.c -o obj/lista_enlazada.o

app_main.o: apps/app_main.c include/lista_enlazada.h
	gcc -I include -Wall -Werror -c apps/app_main.c -o obj/app_main.o

run:
	./bin/app_main.out
# para Windows comenta la linea de arriba y descomenta la linea de abajo
#./bin/app_main.exe	

clean:
	rm -f bin/app_main.out obj/*.o	
# para Windows comenta la linea de arriba y descomenta la linea de abajo
#del bin\app_main.exe obj\*.o 	
