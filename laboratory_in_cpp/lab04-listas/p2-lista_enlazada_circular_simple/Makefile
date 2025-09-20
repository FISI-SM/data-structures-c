# Compilador
CXX = g++
CXXFLAGS = -Wall -g -Iinclude

# Carpetas
SRC_DIR = src
APP_DIR = apps
OBJ_DIR = obj
BIN_DIR = bin

# Archivos
OBJS   = $(OBJ_DIR)/lista_circular.o $(OBJ_DIR)/app_main.o
TARGET = $(BIN_DIR)/app_lista_circular

.PHONY: all clean run

all: $(TARGET)

# Enlazado -> necesita que exista bin/
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilación -> necesita que exista obj/
$(OBJ_DIR)/lista_circular.o: $(SRC_DIR)/lista_circular.cpp include/lista_circular.h | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/app_main.o: $(APP_DIR)/app_main.cpp include/lista_circular.h | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Crear directorios si no existen
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

run: all
	./$(TARGET)

clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)
