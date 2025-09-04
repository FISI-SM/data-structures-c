# === Configuración ===
CC       := gcc
CFLAGS   := -Wall -Wextra -std=c11 -O2 -Iinclude
LDFLAGS  :=

APP_DIR  := apps
SRC_DIR  := src
INC_DIR  := include
OBJ_DIR  := obj
BIN_DIR  := bin

TARGET   := $(BIN_DIR)/app_lista

SRCS := $(APP_DIR)/app_main.c $(SRC_DIR)/lista_enlazada.c
OBJS := $(SRCS:$(APP_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJS := $(OBJS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

.PHONY: all run clean distclean debug

all: $(TARGET)

$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)
	@echo ">> Generado: $@"

$(OBJ_DIR)/%.o: $(APP_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

run: all
	@$(TARGET)

debug: CFLAGS += -g -O0
debug: clean all
	@echo ">> Ejecuta: gdb $(TARGET)"

clean:
	@rm -f $(OBJ_DIR)/*.o
	@echo ">> Limpieza de objetos."

distclean: clean
	@rm -f $(TARGET)
	@echo ">> Limpieza total (binario)."
