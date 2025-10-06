# Reproductor (FLTK + C++) — Lista enlazada simple

Estructura solicitada:
```
apps/
 └── app_main.cpp
bin/
 └── app_lista
include/
 └── lista_enlazada.h
obj/
 ├── app_main.o
 └── lista_enlazada.o
src/
 └── lista_enlazada.cpp
Makefile
README.md
```

## Requisitos

### Ubuntu/Debian
```
sudo apt-get update
sudo apt-get install build-essential fltk1.3-dev
```

### Windows (MSYS2 MINGW64)

Open (search in windows start) the blue terminal called "MSYS2 MINGW64"
```
pacman -Syu
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-fltk make
```

## Compilar
```
make
```
Genera `bin/app_lista` (o `bin/app_lista.exe`).

## Ejecutar
```
./bin/app_lista
```
or
```
make run
```



## Notas
- Navegación no circular (izquierda/derecha solo si hay anterior/siguiente).
- Toda la lógica de la lista está encapsulada en `struct ListaEnlazada` con funciones miembro.
