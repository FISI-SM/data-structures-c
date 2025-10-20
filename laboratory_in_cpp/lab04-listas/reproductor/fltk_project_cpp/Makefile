# FLTK C++ — estructura solicitada
CXX = g++
CXXFLAGS = -Iinclude -Wall -g $(shell fltk-config --cxxflags)
LDFLAGS  = $(shell fltk-config --ldflags)

APP_DIR = apps
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = bin

TARGET = $(BIN_DIR)/app_lista
OBJS = $(OBJ_DIR)/app_main.o $(OBJ_DIR)/lista_enlazada.o

all: $(TARGET)

$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/app_main.o: $(APP_DIR)/app_main.cpp $(INC_DIR)/lista_enlazada.h | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/lista_enlazada.o: $(SRC_DIR)/lista_enlazada.cpp $(INC_DIR)/lista_enlazada.h | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)

run: all
	./$(TARGET)

.PHONY: all clean run
