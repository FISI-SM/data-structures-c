# Compilador
CXX = g++
CXXFLAGS = -Wall -g -Iinclude -std=gnu++17

SRC_DIR = src
APP_DIR = apps
OBJ_DIR = obj
BIN_DIR = bin

OBJS = $(OBJ_DIR)/bplustree_map.o $(OBJ_DIR)/app_main.o
TARGET = $(BIN_DIR)/app_bplustree_map

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/bplustree_map.o: $(SRC_DIR)/bplustree_map.cpp include/bplustree_map.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/app_main.o: $(APP_DIR)/app_main.cpp include/bplustree_map.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)
