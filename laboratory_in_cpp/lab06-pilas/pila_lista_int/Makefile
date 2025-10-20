# === Configuración ===
CC       := g++
CFLAGS   := -Wall -g -Iinclude

APP_DIR  := apps
SRC_DIR  := src
OBJ_DIR  := obj
BIN_DIR  := bin

TARGET   := $(BIN_DIR)/pila_lista_int

# Fuentes y objetos
SRCS := $(APP_DIR)/app_main.cpp $(SRC_DIR)/pila_lista_int.cpp
OBJS := $(SRCS:$(APP_DIR)/%.cpp=$(OBJ_DIR)/%.o)
OBJS := $(OBJS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# === Reglas ===
.PHONY: all run clean distclean debug

all: $(TARGET)

$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJS) -o $@
	@echo ">> Generado: $@"

$(OBJ_DIR)/%.o: $(APP_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Crear directorios si no existen
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)	

run: all
	@$(TARGET)

gdb: debug
	gdb --args $(TARGET)	

debug: CFLAGS += -g -O0
	
debug: clean all
	@echo ">> Ejecuta: gdb $(TARGET)"

clean:
	@rm -f $(OBJ_DIR)/*.o
	@echo ">> Limpieza de objetos."

distclean: clean
	@rm -f $(TARGET)
	@echo ">> Limpieza total (binario)."
