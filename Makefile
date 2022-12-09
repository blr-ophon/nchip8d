INCLUDES= -I ./include
FLAGS= -g -Wall 
OBJECTS= ./build/chip8memory.o ./build/chip8stack.o ./build/chip8keyboard.o ./build/chip8.o ./build/chip8screen.o ./build/display.o ./build/gameinput.o ./build/debuggermain.o ./build/debuggermenus.o ./build/gamemain.o


all: ${OBJECTS}
	mkdir -p ./bin 
	mkdir -p ./build
	gcc ${FLAGS} ${INCLUDES} ./src/main.c ${OBJECTS} -L lSDL2main -lSDL2 -lSDL2_ttf -o ./bin/chip8D

./build/chip8memory.o:src/chip8memory.c
	gcc ${FLAGS} ${INCLUDES} ./src/chip8memory.c -c -o ./build/chip8memory.o

./build/chip8stack.o:src/chip8stack.c
	gcc ${FLAGS} ${INCLUDES} ./src/chip8stack.c -c -o ./build/chip8stack.o

./build/chip8keyboard.o:src/chip8keyboard.c
	gcc ${FLAGS} ${INCLUDES} ./src/chip8keyboard.c -c -o ./build/chip8keyboard.o

./build/chip8screen.o:src/chip8screen.c
	gcc ${FLAGS} ${INCLUDES} ./src/chip8screen.c -c -o ./build/chip8screen.o

./build/chip8.o:src/chip8.c
	gcc ${FLAGS} ${INCLUDES} ./src/chip8.c -c -o ./build/chip8.o

./build/display.o:src/display.c
	gcc ${FLAGS} ${INCLUDES} ./src/display.c -c -o ./build/display.o

./build/gameinput.o:src/gameinput.c
	gcc ${FLAGS} ${INCLUDES} ./src/gameinput.c -c -o ./build/gameinput.o

./build/debuggermain.o:src/debuggermain.c
	gcc ${FLAGS} ${INCLUDES} ./src/debuggermain.c -c -o ./build/debuggermain.o

./build/debuggermenus.o:src/debuggermenus.c
	gcc ${FLAGS} ${INCLUDES} ./src/debuggermenus.c -c -o ./build/debuggermenus.o

./build/gamemain.o:src/gamemain.c
	gcc ${FLAGS} ${INCLUDES} ./src/gamemain.c -c -o ./build/gamemain.o

install:
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f ./bin/chip8D ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/chip8D

clean:
	rm ./build/*
	rm ./bin/*

run:
	./bin/chip8D ./games/INVADERS

debug:
	cgdb --args ./bin/chip8D ./games/INVADERS

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/chip8D\

