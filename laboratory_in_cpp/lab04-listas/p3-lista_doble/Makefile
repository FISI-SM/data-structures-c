# Compilador
CXX = g++
CXXFLAGS = -Wall -g -Iinclude

SRC_DIR = src
APP_DIR = apps
OBJ_DIR = obj
BIN_DIR = bin

OBJS = $(OBJ_DIR)/lista_doble.o $(OBJ_DIR)/app_main.o
TARGET = $(BIN_DIR)/app_lista_doble

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/lista_doble.o: $(SRC_DIR)/lista_doble.cpp include/lista_doble.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/app_main.o: $(APP_DIR)/app_main.cpp include/lista_doble.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)
