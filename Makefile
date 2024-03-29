CC = gcc
OPT = -O0

CFLAGS = -std=c99 -g -Wall $(OPT)

CFLAGS = -std=c99 -g -Wall -Wextra -pedantic $(OPT)


INCLUDES= -I ./include
LIBRARIES= -lSDL2 -lSDL2_ttf

CFILES_DIR := ./src
BUILD_DIR := ./build

CFILES := $(wildcard ./src/*.c)
OBJECTS := $(CFILES:$(CFILES_DIR)/%.c=$(BUILD_DIR)/%.o)
EXEC := ./bin/nchip8D
TESTGAME := ./games/INVADERS
TESTROM := ./tests/chip8-test-suite.ch8


${EXEC}: ${OBJECTS}
	mkdir -p $(dir $@)
	$(CC) ${CFLAGS} ${INCLUDES} ${OBJECTS} -o $@ ${LIBRARIES}

${BUILD_DIR}/%.o: ${CFILES_DIR}/%.c
	mkdir -p $(dir $@)
	$(CC) ${CFLAGS} ${INCLUDES} -c $< -o $@

clean:
	rm -rf ${OBJECTS} 
	rm -rf ${EXEC}

run: ${EXEC}
	$^ ${TESTGAME}

testrom: ${EXEC}
	$^ ${TESTROM}

install:
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f ${EXEC} ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/nchip8D

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/nchip8D\

debug: ${EXEC}
	cgdb --args $^ ${TESTGAME}

