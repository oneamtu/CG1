CC=g++
EXECUTABLE=cg1

.PHONY: test

all: main test

main: main.cpp
	g++ main.cpp TriangleMesh.cpp -o cg1
	
test:
	cg1 MIT_teapot.obj