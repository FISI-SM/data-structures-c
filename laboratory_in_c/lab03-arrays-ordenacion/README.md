# Guía de Compilación y Ejecución con Make

Este documento explica cómo compilar y ejecutar un proyecto en C usando **Make** tanto en **Linux** como en **Windows (MSYS2/MinGW64)**.  

---

## 🔹 1. En Linux (Ubuntu/Debian/Fedora, etc.)

### Instalar `make` y `gcc`
```bash
sudo apt update && sudo apt install build-essential   # Ubuntu/Debian
# o
sudo dnf groupinstall "Development Tools"            # Fedora
```

### Compilar con `make`
Ubícate en la carpeta de tu proyecto (donde está el `Makefile`):
```bash
cd ~/projects/data-structures-c/laboratory/lab03-arrays-ordenacion/p01-complex_app_basic_make
make
```

Esto leerá el `Makefile` y compilará el programa.  

### Ejecutar
Si el ejecutable se llama `complex_app.out`:
```bash
./complex_app.out
```

Si tienes una regla en tu `Makefile` llamada `run`, basta con:
```bash
make run
```

---

## 🔹 2. En Windows (MSYS2 / MinGW64)

### Instalar `make` y `gcc`
En la terminal **MSYS2 MinGW64** corre:
```bash
pacman -Syu    # actualizar paquetes
pacman -S make mingw-w64-x86_64-gcc
```

### Compilar con `make`
Al igual que en Linux:
```bash
cd ~/projects/data-structures-c/laboratory/lab03-arrays-ordenacion/p01-complex_app_basic_make
make
```

Esto generará el ejecutable (ejemplo: `complex_app.exe`).  

### Ejecutar
```bash
./complex_app.exe
```

O si tu `Makefile` tiene la regla `run`:
```bash
make run
```

---

## 🔹 3. Notas importantes
- No ejecutes `Makefile` directamente (`bash: Makefile: command not found`), siempre usa `make`.
- Verifica que tu archivo se llame **Makefile** (con M mayúscula) o **makefile**, porque `make` lo busca con ese nombre por defecto.
- En Windows, el ejecutable termina en `.exe`; en Linux normalmente no tiene extensión.

---

✅ Con esto puedes compilar y ejecutar tu proyecto sin problemas en ambos sistemas operativos.


---

## 🔹 4. Nota para usuarios de Git Bash en Windows
Si estás usando **Git Bash** en lugar de MSYS2, no tendrás `make` disponible por defecto.  
En su lugar, cuando instales MinGW, el comando suele llamarse:

```bash
mingw32-make
```

Por lo tanto, en Git Bash deberás compilar así:

```bash
mingw32-make
```

y ejecutar el programa normalmente con:

```bash
./programa.exe
```

