# Proyecto FLTK en C++ con estructura apps/, src/, include/, obj/, bin/
CXX = g++
CXXFLAGS = -Iinclude -Wall -g $(shell fltk-config --cxxflags)
LDFLAGS = $(shell fltk-config --ldflags)

SRC_DIR = src
APP_DIR = apps
OBJ_DIR = obj
BIN_DIR = bin
INC_DIR = include

OBJS = $(OBJ_DIR)/gui_music.o $(OBJ_DIR)/app_main.o
TARGET = $(BIN_DIR)/gui_music_fltk_cpp

all: $(TARGET)

$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/gui_music.o: $(SRC_DIR)/gui_music.cpp $(INC_DIR)/gui_music.hpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/app_main.o: $(APP_DIR)/app_main.cpp $(INC_DIR)/gui_music.hpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)

.PHONY: all clean
