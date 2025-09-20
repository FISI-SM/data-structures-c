# Proyecto GTK con estructura apps/, src/, include/, obj/, bin/
CC        = gcc

# Cambia esta línea a gtk+-3.0 si usas GTK 3:
GTK_PKG   = gtk4

# Toma flags de pkg-config (mejor en variables separadas)
GTK_CFLAGS := $(shell pkg-config --cflags $(GTK_PKG))
GTK_LIBS   := $(shell pkg-config --libs   $(GTK_PKG))

CFLAGS    = -Iinclude -Wall -g $(GTK_CFLAGS)
LDFLAGS   = $(GTK_LIBS)

SRC_DIR = src
APP_DIR = apps
OBJ_DIR = obj
BIN_DIR = bin
INC_DIR = include

OBJS   = $(OBJ_DIR)/gui_music.o $(OBJ_DIR)/app_main.o
TARGET = $(BIN_DIR)/gui_music_gtk

all: $(TARGET)

$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/gui_music.o: $(SRC_DIR)/gui_music.c $(INC_DIR)/gui_music.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/app_main.o: $(APP_DIR)/app_main.c $(INC_DIR)/gui_music.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)

.PHONY: all clean
