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
PYSCRIPT=./pyscript
ZMQ_INCLUDE=-I/usr/local/include
ZMQ_LIB=-L/usr/local/lib -lzmq
PROTOBUF_LIB=-L/usr/local/lib -lprotobuf -pthread

MKDIR_P=mkdir -p
.PHONY: directories

all: directories $(BIN_DIR)/nlp_service_main Worker Leader

MSGmodule: $(BUILD_DIR)/titlebook.pb.o $(BUILD_DIR)/cppMSGmodule.o

Worker: $(BIN_DIR)/Worker

Leader: $(BIN_DIR)/Leader.py $(BUILD_DIR)/pyMSGmodule.py $(BUILD_DIR)/titlebook_pb2.py

directories: $(BUILD_DIR)

${BUILD_DIR}:
	$(MKDIR_P) $(BUILD_DIR)
	$(MKDIR_P) $(BIN_DIR)

$(BIN_DIR)/nlp_service_main: $(BUILD_DIR)/nlp_service_main.o $(BUILD_DIR)/combinition.o $(BUILD_DIR)/libClassifier.o $(BUILD_DIR)/sqlite3.o $(BUILD_DIR)/TC_process.o
	$(LINK) $(LDFLAGS) $^ -o $@

$(BUILD_DIR)/combinition.o: $(SRC)/combinition.cpp
	$(CXX) $^ $(CFLAGS) -c -o $@

$(BUILD_DIR)/libClassifier.o: $(SRC)/libClassifier.cpp
	$(CXX) $^ $(CFLAGS) -c -o $@

$(BUILD_DIR)/sqlite3.o: $(SRC)/sqlite3.c
	$(C) $^ $(CFLAGS) -c -o $@

$(BUILD_DIR)/TC_process.o: $(SRC)/TC_process.cpp
	$(CXX) $^ $(CFLAGS) -c -o $@

$(BUILD_DIR)/nlp_service_main.o: $(TOOL_SRC)/nlp_service_main.cpp
	$(CXX) $^ $(CFLAGS) -c -o $@

$(BUILD_DIR)/titlebook.pb.o: $(SRC)/titlebook.pb.cc
	$(CXX) $^ $(CFLAGS) -c -o $@

$(BUILD_DIR)/cppMSGmodule.o: $(SRC)/cppMSGmodule.cpp
	$(CXX) $^ $(CFLAGS) -c -o $@

$(BIN_DIR)/Worker: $(TOOL_SRC)/Worker.cpp $(BUILD_DIR)/titlebook.pb.o $(BUILD_DIR)/cppMSGmodule.o $(BUILD_DIR)/combinition.o $(BUILD_DIR)/libClassifier.o $(BUILD_DIR)/sqlite3.o $(BUILD_DIR)/TC_process.o
	$(CXX) $^ $(CFLAGS) $(ZMQ_INCLUDE) $(ZMQ_LIB) $(PROTOBUF_LIB) $(LDFLAGS) -o $@

$(BIN_DIR)/Leader.py: $(PYSCRIPT)/Leader.py
	cp $^ $@

$(BUILD_DIR)/pyMSGmodule.py: $(PYSCRIPT)/pyMSGmodule.py
	cp $^ $@

$(BUILD_DIR)/titlebook_pb2.py: $(PYSCRIPT)/titlebook_pb2.py
	cp $^ $@

clean:
	rm -rf build
