CXX=g++
CXXFLAGS=-Wall -g -Iinclude -std=gnu++17
SRC_DIR=src
APP_DIR=apps
OBJ_DIR=obj
BIN_DIR=bin
OBJS=$(OBJ_DIR)/arbol_binario_int.o $(OBJ_DIR)/app_main.o
TARGET=$(BIN_DIR)/app_arbol_binario_int
all: $(TARGET)
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^
$(OBJ_DIR)/arbol_binario_int.o: $(SRC_DIR)/arbol_binario_int.cpp include/arbol_binario_int.h
	$(CXX) $(CXXFLAGS) -c $< -o $@
$(OBJ_DIR)/app_main.o: $(APP_DIR)/app_main.cpp include/arbol_binario_int.h
	$(CXX) $(CXXFLAGS) -c $< -o $@
clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)
