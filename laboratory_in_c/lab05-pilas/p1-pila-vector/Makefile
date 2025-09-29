all: app_main

app_main: app_main.o pila_como_vector.o  
	gcc obj/app_main.o obj/pila_como_vector.o -o bin/app_main.out	

pila_como_vector.o: src/pila_como_vector.c include/pila_como_vector.h
	gcc -I include -Wall -Werror -c src/pila_como_vector.c -o obj/pila_como_vector.o

app_main.o: apps/app_main.c include/pila_como_vector.h
	gcc -I include -Wall -Werror -c apps/app_main.c -o obj/app_main.o

run:
	./bin/app_main.out	

clean:
	rm -f bin/app_main.out obj/*.o	
#del /F /A bin\app_main.out obj\*.o 	
