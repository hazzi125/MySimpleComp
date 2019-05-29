GCC = gcc -Wall -Werror -std=c99
OBJ = build/myterm.o build/myBigChars.o build/mySimpleComputer.o build/showComp.o build/myReadkey.o build/curs_work.o build/trans.o build/trans_basic.o
HEAD = src/myterm.h src/myBigChars.h src/mySimpleComputer.h src/showComp.h src/myReadkey.h src/curs_work.h src/trans.h src/trans_basic.h

.PHONY: clean

all: bin build default

default: bin/EXE

bin/EXE: build/main.o $(OBJ)
	$(GCC) build/main.o $(OBJ) -o bin/EXE

build/myBigChars.o: src/myBigChars.c src/myBigChars.h
	$(GCC) -c src/myBigChars.c -o build/myBigChars.o

build/myterm.o: src/myterm.c src/myterm.h
	$(GCC) -c src/myterm.c -o build/myterm.o

build/mySimpleComputer.o: src/mySimpleComputer.c src/mySimpleComputer.h
	$(GCC) -c src/mySimpleComputer.c -o build/mySimpleComputer.o

build/showComp.o: src/showComp.c src/showComp.h
	$(GCC) -c src/showComp.c -o build/showComp.o

build/myReadkey.o: src/myReadkey.c src/myReadkey.h
	$(GCC) -c src/myReadkey.c -o build/myReadkey.o

build/curs_work.o: src/curs_work.c src/curs_work.h
	$(GCC) -c src/curs_work.c -o build/curs_work.o

build/trans.o: src/trans.c src/trans.h
	$(GCC) -c src/trans.c -o build/trans.o

build/trans_basic.o: src/trans_basic.c src/trans_basic.h
	$(GCC) -c src/trans_basic.c -o build/trans_basic.o

build/main.o: $(HEAD)
	gcc -Wall -Werror -c src/main.c -o build/main.o

bin:
	mkdir bin

build:
	mkdir build

clean:
	rm -rf bin build
