CXX=g++
CXXFLAGS=-Wall -g -Iinclude -std=gnu++17
SRC_DIR=src
APP_DIR=apps
OBJ_DIR=obj
BIN_DIR=bin
OBJS=$(OBJ_DIR)/abb_int.o $(OBJ_DIR)/app_main.o
TARGET=$(BIN_DIR)/app_abb_int
all: $(TARGET)
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^
$(OBJ_DIR)/abb_int.o: $(SRC_DIR)/abb_int.cpp include/abb_int.h
	$(CXX) $(CXXFLAGS) -c $< -o $@
$(OBJ_DIR)/app_main.o: $(APP_DIR)/app_main.cpp include/abb_int.h
	$(CXX) $(CXXFLAGS) -c $< -o $@
clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)
