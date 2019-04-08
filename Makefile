GCC = gcc -Wall -Werror -std=c99
OBJ = build/myterm.o build/myBigChars.o
HEAD = src/myterm.h src/myBigChars.h

.PHONY: clean

all: bin build default

default: bin/EXE

bin/EXE: build/main.o $(OBJ)
	$(GCC) build/main.o $(OBJ) -o bin/EXE

build/myBigChars.o: src/myBigChars.c src/myBigChars.h
	$(GCC) -c src/myBigChars.c -o build/myBigChars.o

build/myterm.o: src/myterm.c src/myterm.h
	$(GCC) -c src/myterm.c -o build/myterm.o

build/main.o: $(HEAD)
	$(GCC) -c src/main.c -o build/main.o

bin:
	mkdir bin

build:
	mkdir build

clean:
	rm -rf bin build
