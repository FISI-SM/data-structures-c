# Compilador a utilizar (GNU C Compiler)
CC      := gcc

# Flags de compilación:
#  -Wall y -Wextra activan advertencias útiles
#  -std=c11 fija el estándar de C
#  -O2 aplica optimizaciones moderadas
CFLAGS  := -Wall -Wextra -std=c11 -O2

# Nombre base del ejecutable final (sin ruta ni extensión)
TARGET  := complex_calc

# Lista de fuentes en C del proyecto
SRCS    := main.c complex.c

# Regla de sustitución: convierte cada .c de SRCS en su .o correspondiente
OBJS    := $(SRCS:.c=.o)

# Objetivos “falsos” (no generan un archivo): evitan conflictos con archivos llamados igual
.PHONY: all run clean distclean

# Objetivo por defecto: construir el ejecutable
all: $(TARGET)

# Regla de enlace: genera el ejecutable a partir de los objetos
#  $@  = nombre del objetivo (aquí, $(TARGET))
#  $(CC) usa las CFLAGS también al enlazar (práctico para LTO o warnings de link)
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@          # Enlaza todos los .o en el binario final
	@echo ">> Generado: $@"                # Mensaje informativo (silenciado con @)

# Regla patrón: compila cualquier .c en su .o
#  $<  = primera dependencia (el .c correspondiente)
#  -c  = compilar sin enlazar
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@            # Compila archivo fuente a objeto

# Objetivo de conveniencia: compila y ejecuta un ejemplo de uso
run: all
	@./$(TARGET) add 1 2 3 4               # Ejecuta el binario con parámetros de prueba

# Limpia los objetos intermedios
clean:
	@rm -f *.o                              # Elimina todos los .o del directorio actual
	@echo ">> Limpieza de objetos."         # Mensaje informativo

# Limpieza total: además de objetos, borra el ejecutable
distclean: clean
	@rm -f $(TARGET)                        # Elimina el binario final
	@echo ">> Limpieza total."              # Mensaje informativo

