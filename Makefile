CC=g++
EXECUTABLE=cg1

.PHONY: test

all: main

main: main.cpp
	g++ main.cpp TriangleMesh.cpp Image.cpp -o cg1 -g
	
test:
	cg1 MIT_teapot.obj