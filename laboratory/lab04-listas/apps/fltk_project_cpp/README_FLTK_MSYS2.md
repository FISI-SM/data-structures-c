# FLTK en Windows con MSYS2 (Opción A)

Este README explica cómo **instalar FLTK** y **compilar** un proyecto FLTK (C o C++) en **Windows** usando **MSYS2 MINGW64**.

> Recomendado porque trae `g++`, `make` y `fltk-config` listos para usar.


## 📦 TL;DR (comandos rápidos)

1) Abre **MSYS2 MINGW64** (no MSYS, no UCRT, no CLANG).  
2) Actualiza e instala toolchain + FLTK:
```bash
pacman -Syu
# si te pide reiniciar la terminal, ciérrala, vuelve a abrir MINGW64 y repite:
pacman -Syu
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-fltk make
```
3) Verifica `fltk-config`:
```bash
which fltk-config
# /mingw64/bin/fltk-config
```
4) Compila tu proyecto (con Makefile basado en fltk-config):
```bash
make            # o: mingw32-make
./bin/gui_music_fltk_cpp.exe   # (C++)  ó  ./bin/gui_music_fltk.exe (C)
```


## 🧰 Instalación paso a paso

### 1) Instalar MSYS2
- Descarga MSYS2 desde https://www.msys2.org/ e instálalo con valores por defecto.
- Abre **MSYS2 MINGW64** desde el menú inicio (importante).

### 2) Actualizar el sistema
```bash
pacman -Syu
# si pide cerrar la terminal, hazlo y vuelve a abrir "MSYS2 MINGW64"
pacman -Syu
```

### 3) Instalar compilador, FLTK y make
```bash
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-fltk make
```
Esto instala:
- `g++`/`gcc` para MINGW64
- Bibliotecas y headers de **FLTK**
- Herramienta `fltk-config` (clave para flags de compilación/enlace)

### 4) Verificar instalación
```bash
which g++
which fltk-config
fltk-config --version
```
Debes ver rutas bajo `/mingw64/bin` y una versión válida de FLTK (1.3.x o 1.4.x).


## ▶️ Compilar y ejecutar tu proyecto

### Estructura esperada
```
apps/        -> app_main.cpp (o .c)
src/         -> gui_music.cpp (o .c)
include/     -> gui_music.hpp/.h
obj/         -> objetos .o (se crean en build)
bin/         -> binarios
Makefile
```

### Makefile (resumen)
El Makefile usa `fltk-config` para obtener flags correctas:
```make
CXXFLAGS = -Iinclude -Wall -g $(shell fltk-config --cxxflags)
LDFLAGS  = $(shell fltk-config --ldflags)
```
Así te evitas escribir libs y rutas a mano.

### Compilación
```bash
make              # o mingw32-make
```
Binario:
- C++: `bin/gui_music_fltk_cpp.exe`
- C:   `bin/gui_music_fltk.exe`

### Ejecución
```bash
./bin/gui_music_fltk_cpp.exe
# o
./bin/gui_music_fltk.exe
```


## 🧪 Prueba rápida (Hello FLTK)
```bash
cat > hello.cpp << "EOF"
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
int main(){
  Fl_Window win(300,200,"Hello FLTK");
  win.show();
  return Fl::run();
}
EOF

g++ hello.cpp -o hello.exe `fltk-config --cxxflags --ldflags`
./hello.exe
```


## 💡 Usando Git Bash (opcional)
Si prefieres **Git Bash** en vez de la terminal MINGW64, agrega MSYS2 al `PATH` antes de compilar:
```bash
export PATH="/c/msys64/mingw64/bin:$PATH"
which fltk-config   # debe mostrar /c/msys64/mingw64/bin/fltk-config
```


## ❗ Troubleshooting

- **`fltk-config: command not found`**  
  Estás en la terminal equivocada. Abre **MSYS2 MINGW64** o exporta el `PATH` como arriba.

- **Errores “undefined reference” al linkear**  
  Asegúrate de **usar `fltk-config`** en el Makefile:
  ```make
  CXXFLAGS = ... $(shell fltk-config --cxxflags)
  LDFLAGS  = $(shell fltk-config --ldflags)
  ```

- **Se abre MSYS (no MINGW64)**  
  Repite el proceso pero con el acceso directo **MSYS2 MINGW64**.  
  (En la barra de título debe decir `MINGW64` y el prompt suele incluir `MINGW64`.)

- **Quiero toolchain UCRT64 en vez de MINGW64**  
  Es posible, pero usa los paquetes equivalentes `ucrt64` y su terminal **UCRT64**.  
  Para simplificar la clase, mejor MINGW64.

---

¡Listo! Con esto deberías poder instalar FLTK y compilar cualquiera de los proyectos entregados (C o C++) en Windows usando MSYS2.
