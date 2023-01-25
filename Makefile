CC = gcc
OPT = -O2

CFLAGS = -std=c99 -g -Wall $(OPT)

CFLAGS = -std=c99 -g -Wall -Wextra -pedantic $(OPT)


INCLUDES= -I ./include
LIBRARIES= -lSDL2 -lSDL2_ttf

CFILES_DIR := ./src
BUILD_DIR := ./build

CFILES := $(wildcard ./src/*.c)
OBJECTS := $(CFILES:$(CFILES_DIR)/%.c=$(BUILD_DIR)/%.o)
EXEC := ./bin/chip8D
ARGS := ./games/BRIX


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
	$^ ${ARGS}

install:
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f ./bin/chip8D ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/chip8D

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/chip8D\

debug: ${EXEC}
	cgdb --args $^ ${ARGS}

