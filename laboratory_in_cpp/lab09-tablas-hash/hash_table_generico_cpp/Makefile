# Compilador
CXX = g++
CXXFLAGS = -Wall -g -Iinclude -std=gnu++17

SRC_DIR = src
APP_DIR = apps
OBJ_DIR = obj
BIN_DIR = bin

OBJS = $(OBJ_DIR)/hash_table.o $(OBJ_DIR)/app_main.o
TARGET = $(BIN_DIR)/app_hash_table

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/hash_table.o: $(SRC_DIR)/hash_table.cpp include/hash_table.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/app_main.o: $(APP_DIR)/app_main.cpp include/hash_table.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)
