C=gcc
CXX=g++ -std=c++11
CFLAGS=-I./include
LDFLAGS=-Wl,--no-as-needed -ldl -pthread
LINK=g++

SRC=./src
INCLUDE=./include
BUILD_DIR=./build
BIN_DIR=./build/bin
TOOL_SRC=./tool

MKDIR_P=mkdir -p
.PHONY: directories

all: directories $(BIN_DIR)/main

directories: $(BUILD_DIR)

${BUILD_DIR}:
	$(MKDIR_P) $(BUILD_DIR)
	$(MKDIR_P) $(BIN_DIR)

$(BIN_DIR)/main: $(BUILD_DIR)/main.o $(BUILD_DIR)/combinition.o $(BUILD_DIR)/libClassifier.o $(BUILD_DIR)/sqlite3.o $(BUILD_DIR)/TC_process.o
	$(LINK) $(LDFLAGS) $^ -o $@

$(BUILD_DIR)/combinition.o: $(SRC)/combinition.cpp
	$(CXX) $^ $(CFLAGS) -c -o $@

$(BUILD_DIR)/libClassifier.o: $(SRC)/libClassifier.cpp
	$(CXX) $^ $(CFLAGS) -c -o $@

$(BUILD_DIR)/sqlite3.o: $(SRC)/sqlite3.c
	$(C) $^ $(CFLAGS) -c -o $@

$(BUILD_DIR)/TC_process.o: $(SRC)/TC_process.cpp
	$(CXX) $^ $(CFLAGS) -c -o $@

$(BUILD_DIR)/main.o: $(TOOL_SRC)/main.cpp
	$(CXX) $^ $(CFLAGS) -c -o $@

clean:
	rm -rf build
