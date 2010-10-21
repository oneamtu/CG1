CC=g++
BIN_DIR=bin
EXECUTABLE=${BIN_DIR}/cg1

.PHONY: test

all: main

main: main.cpp
#	mkdir -p ${BIN_DIR}
	${CC} main.cpp TriangleMesh.cpp Image.cpp -o cg1 -g
	
test:
	cg1 MIT_teapot.obj