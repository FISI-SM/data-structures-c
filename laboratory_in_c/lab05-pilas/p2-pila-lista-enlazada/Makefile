all: app_main

app_main: app_main.o pila_como_lista_enlazada.o  
	gcc obj/app_main.o obj/pila_como_lista_enlazada.o -o bin/app_main.out	
# Para Windows, comentar la linea anterior y descomentar la siguiente
# gcc obj/app_main.o obj/pila_como_lista_enlazada.o -o bin/app_main.exe	

pila_como_lista_enlazada.o: src/pila_como_lista_enlazada.c include/pila_como_lista_enlazada.h
	gcc -I include -Wall -Werror -c src/pila_como_lista_enlazada.c -o obj/pila_como_lista_enlazada.o

app_main.o: apps/app_main.c include/pila_como_lista_enlazada.h
	gcc -I include -Wall -Werror -c apps/app_main.c -o obj/app_main.o

run:
	./bin/app_main.out
# Para Windows, comentar la linea anterior y descomentar la siguiente
# .\bin\app_main.exe	

clean:
	rm -f bin/app_main.out obj/*.o	
# Para Windows, comentar la linea anterior y descomentar la siguiente
# del bin\app_main.exe obj\*.o 	
