# Calculadora de Números Complejos (C + Makefile)

Proyecto ejemplo con estructura modular y TAD `Complex` para **sumar, restar y multiplicar**.

## Estructura
```
apps/   -> programa principal (CLI)
src/    -> implementación del TAD Complex
include/-> cabeceras públicas
obj/    -> objetos compilados
bin/    -> ejecutable final
```

## Compilación
```bash
make
```

## Ejecución (CLI)
El binario se llama `complex_calc` y admite tres operaciones: `add`, `sub`, `mul`.

```bash
./bin/complex_calc add 1 2 3 4   # (1+2i) + (3+4i)
./bin/complex_calc sub 5 0 2 -3  # (5+0i) - (2-3i)
./bin/complex_calc mul -1 0 0 2  # (-1+0i) * (0+2i)
```

### Salida de ejemplo
```
A = 1.000000 + 2.000000i
B = 3.000000 + 4.000000i
Resultado (add) = 4.000000 + 6.000000i
```

## Compilación manual (sin Makefile)
```bash
gcc -Wall -Wextra -std=c11 -Iinclude -c src/complex.c -o obj/complex.o
gcc -Wall -Wextra -std=c11 -Iinclude -c apps/app_main.c -o obj/app_main.o
gcc obj/complex.o obj/app_main.o -o bin/complex_calc
```
