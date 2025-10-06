# GUI Music (FLTK) — Estructura Makefile

Estructura:
```
apps/        -> app_main.cpp (FLTK + GUI)
src/         -> gui_music.c (lista simple en C)
include/     -> gui_music.h (API C con extern "C" para enlazar con C++)
obj/         -> objetos .o
bin/         -> binarios
Makefile
```

## Requisitos (Ubuntu/Debian)
```
sudo apt-get update
sudo apt-get install build-essential fltk1.3-dev
```
(Este paquete instala `fltk-config` que usamos en el Makefile).

## Compilar
```
make
```
El ejecutable se genera en `bin/gui_music_fltk`.

## Ejecutar
```
./bin/gui_music_fltk
```

## Windows (MSYS2 Mingw64)
```
pacman -Syu
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-fltk
mingw32-make
./bin/gui_music_fltk.exe
```
(Asegúrate de estar en la terminal **MSYS2 MINGW64** y que `fltk-config` esté en PATH).
