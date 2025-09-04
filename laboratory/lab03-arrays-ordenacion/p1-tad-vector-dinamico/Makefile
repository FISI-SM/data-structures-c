all: app_main

app_main: app_main.o vector_dinamico.o  
	gcc obj/app_main.o obj/vector_dinamico.o -o bin/app_main.out	

vector_dinamico.o: src/vector_dinamico.c include/vector_dinamico.h
	gcc -I include -Wall -Werror -c src/vector_dinamico.c -o obj/vector_dinamico.o

app_main.o: apps/app_main.c include/vector_dinamico.h
	gcc -I include -Wall -Werror -c apps/app_main.c -o obj/app_main.o

run:
	./bin/app_main.out	

clean:
	rm -f bin/app_main.out obj/*.o	
#del /F /A bin\app_main.out obj\*.o 	
