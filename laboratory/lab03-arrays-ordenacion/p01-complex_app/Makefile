CC      := gcc
CFLAGS  := -Wall -Wextra -std=c11 -O2
TARGET  := complex_calc
SRCS    := main.c complex.c
OBJS    := $(SRCS:.c=.o)

.PHONY: all run clean distclean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@
	@echo ">> Generado: $@"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	@./$(TARGET) add 1 2 3 4

clean:
	@rm -f *.o
	@echo ">> Limpieza de objetos."

distclean: clean
	@rm -f $(TARGET)
	@echo ">> Limpieza total."
