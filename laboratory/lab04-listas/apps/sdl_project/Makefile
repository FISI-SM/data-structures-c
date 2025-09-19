CC = gcc
CFLAGS = -Iinclude -Wall -g
LDFLAGS = `sdl2-config --cflags --libs` -lSDL2_ttf

SRC_DIR = src
APP_DIR = apps
OBJ_DIR = obj
BIN_DIR = bin
INC_DIR = include

OBJS = $(OBJ_DIR)/complex.o $(OBJ_DIR)/app_main.o
TARGET = $(BIN_DIR)/gui_music_sdl

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/complex.o: $(SRC_DIR)/gui_music.c $(INC_DIR)/gui_music.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/app_main.o: $(APP_DIR)/app_main.c $(INC_DIR)/gui_music.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)

.PHONY: all clean
