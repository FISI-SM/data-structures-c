# Compilador
CXX = g++
CXXFLAGS = -Wall -g -Iinclude -std=gnu++17

SRC_DIR = src
APP_DIR = apps
OBJ_DIR = obj
BIN_DIR = bin

OBJS = $(OBJ_DIR)/cola_lista.o $(OBJ_DIR)/app_main.o
TARGET = $(BIN_DIR)/app_cola_lista

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/cola_lista.o: $(SRC_DIR)/cola_lista.cpp include/cola_lista.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/app_main.o: $(APP_DIR)/app_main.cpp include/cola_lista.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)
