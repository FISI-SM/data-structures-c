# Compilador
CXX = g++
CXXFLAGS = -Wall -g -Iinclude

# Carpetas
SRC_DIR = src
APP_DIR = apps
OBJ_DIR = obj
BIN_DIR = bin

# Archivos
OBJS = $(OBJ_DIR)/lista_enlazada.o $(OBJ_DIR)/app_main.o
TARGET = $(BIN_DIR)/app_lista

# Regla principal
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/lista_enlazada.o: $(SRC_DIR)/lista_enlazada.cpp include/lista_enlazada.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/app_main.o: $(APP_DIR)/app_main.cpp include/lista_enlazada.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpiar
clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)
