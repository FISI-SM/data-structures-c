# GUI Music (FLTK, C++) — Estructura Makefile

Estructura:
```
apps/        -> app_main.cpp (FLTK + GUI)
src/         -> gui_music.cpp (lista simple en C++)
include/     -> gui_music.hpp (API C++)
obj/         -> objetos .o
bin/         -> binarios
Makefile
```

## Requisitos (Ubuntu/Debian)
```
sudo apt-get update
sudo apt-get install build-essential fltk1.3-dev
```
(`fltk1.3-dev` instala `fltk-config` que se usa en el Makefile).

## Compilar
```
make
```
El ejecutable se genera en `bin/gui_music_fltk_cpp`.

## Ejecutar
```
./bin/gui_music_fltk_cpp
```

## Windows (MSYS2 Mingw64)
```
pacman -Syu
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-fltk
mingw32-make
./bin/gui_music_fltk_cpp.exe
```
(Asegúrate de estar en la terminal **MSYS2 MINGW64** y que `fltk-config` esté en PATH).
