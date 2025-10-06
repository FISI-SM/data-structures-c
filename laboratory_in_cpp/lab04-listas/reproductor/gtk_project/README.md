# GUI Music (GTK) — Estructura Makefile

Estructura:
```
apps/        -> app_main.c (GTK + lógica de interfaz)
src/         -> gui_music.c (lista simple)
include/     -> gui_music.h (prototipos)
obj/         -> objetos .o
bin/         -> binarios
Makefile
```
## Requisitos (Linux)
```
sudo apt-get update
sudo apt-get install build-essential pkg-config libgtk-3-dev
```
## Compilar
```
make
```
El ejecutable se genera en `bin/gui_music_gtk`.

## Ejecutar
```
./bin/gui_music_gtk
```
