GCC = gcc -Wall -Werror -std=c99

.PHONY: clean

all: bin build default

default: bin/MyTerm

bin/MyTerm: build/main.o build/myterm.o
	$(GCC) build/main.o build/myterm.o -o bin/MyTerm

build/myterm.o: src/myterm.c src/myterm.h
	$(GCC) -c src/myterm.c -o build/myterm.o

build/main.o: src/main.c src/myterm.h
	$(GCC) -c src/main.c -o build/main.o

bin:
	mkdir bin

build:
	mkdir build

clean:
	rm -rf bin build
