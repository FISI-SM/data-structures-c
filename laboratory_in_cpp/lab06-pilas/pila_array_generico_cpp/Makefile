# Compilador
CXX = g++
CXXFLAGS = -Wall -g -Iinclude -std=gnu++17

# Carpetas
SRC_DIR = src
APP_DIR = apps
OBJ_DIR = obj
BIN_DIR = bin

# Archivos
OBJS = $(OBJ_DIR)/pila_array.o $(OBJ_DIR)/app_main.o
TARGET = $(BIN_DIR)/app_pila_array

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/pila_array.o: $(SRC_DIR)/pila_array.cpp include/pila_array.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/app_main.o: $(APP_DIR)/app_main.cpp include/pila_array.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)
